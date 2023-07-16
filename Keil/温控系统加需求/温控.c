#include <reg51.h>
#include <intrins.h>
#include <LCD12864.h>
#include <ds1302.h>

#include <word.h>
#include <18b20.h>
#include <delay.h>
#include <key.h>
	
uchar time_data[6]={20,13,17,11,21,14};

sbit relay_jiare=P1^0;  // 加热制冷与蜂鸣器引脚定义
sbit relay_zhileng=P1^1;
sbit buzzer=P1^4;

uint setL = 25;  		// 设置温度下限
uint setH = 30; 		// 设置温度上限
uchar DisFlag = 0;  // 更新显示标志
uchar SetFlag = 0;  // 设置参数标志
uchar pageFlag = 0;	// 设置

uchar i = 0;	// 切换页面清屏
uchar j = 0;
uchar z = 0;

uint time2ms=0;		// 定时计数
uint buzLater=0;  // 蜂鸣器累加检测

uint temp1;								// 读取温度初始值
float temperature = 0;				// 实际温度值
uint temp = 0;	// 存放计算温度值
uchar read_temp_flag = 1;			// 定义读温度标志

void temp_show(); 	// 温控部分
void check_key();   // 按键检查
void init_timer0();   // 定时器初始化

void show_ds1302(uchar *time)
{
	show_num(1,0,8,num+16*2);//2
	show_num(1,0,16,num+16*0);//0
	show_num(1,0,24,num+16*(time[0]/10));//年 十位
	show_num(1,0,32,num+16*(time[0]%10));//年 个位
	
	show_num(1,0,56,num+16*(time[1]/10));//月 十位
	show_num(2,0,0,num+16*(time[1]%10));//月 个位
	
	show_num(2,0,24,num+16*(time[2]/10));//日 十位
	show_num(2,0,32,num+16*(time[2]%10));//日 个位
	
	show_num(1,2,32,num+16*(time[3]/10));//时 十位
	show_num(1,2,40,num+16*(time[3]%10));//时 个位
	
	show_num(1,2,56,num+16*(time[4]/10));//分 十位
	show_num(2,2,0,num+16*(time[4]%10));//分 个位
	
	show_num(2,2,16,num+16*(time[5]/10));//秒 十位
	show_num(2,2,24,num+16*(time[5]%10));//秒 个位
}

void init_words()
{
	show_ch(1,0,40,ch1+32*0); // 年
	show_ch(2,0,8,ch1+32*1); // 月
	show_ch(2,0,40,ch1+32*2); // 日
	show_num(1,2,48,num+16*14); // ：
	show_num(2,2,8,num+16*14); // ：
	show_ch(1,4,0,ch1+32*4); // 当
	show_ch(1,4,16,ch1+32*5); // 前
	show_num(1,4,56,num+16*11); // .
	show_ch(2,4,8,ch1+32*3); // ℃
	show_ch(1,6,40,ch1+32*3); // ℃
	show_ch(2,6,40,ch1+32*3); // ℃
//	show_im(1,2,0*16,image1);
}

void init_welcom()
{
	show_im(1,2,0,image1+128*1);
	show_im(1,2,32,image1+128*2);
	show_im(2,2,0,image1+128*3);
	show_im(2,2,32,image1+128*4);
}

void init_name()
{
	show_ch(1,1,24,ch1+32*17); // 机电1903班
	show_ch(1,1,40,ch1+32*18);
	show_num(1,1,56,num+16*1);
	show_num(2,1,0,num+16*9);
	show_num(2,1,8,num+16*0);
	show_num(2,1,16,num+16*3);
	show_ch(2,1,24,ch1+32*19);
	show_ch(1,3,40,ch1+32*11); // 王一博
	show_num(1,3,56,num+16*16);
	show_num(2,3,0,num+16*16);
	show_ch(2,3,8,ch1+32*13);
	show_num(1,5,16,num+16*1); // 19405010322
	show_num(1,5,24,num+16*9);
	show_num(1,5,32,num+16*4);
	show_num(1,5,40,num+16*0);
	show_num(1,5,48,num+16*5);
	show_num(1,5,56,num+16*0);
	show_num(2,5,0,num+16*1);
	show_num(2,5,8,num+16*0);
	show_num(2,5,16,num+16*3);
	show_num(2,5,24,num+16*2);
	show_num(2,5,32,num+16*2);
}

void main()
{
	init_timer0();
	InitLCD();
	ClearScreen(0);
	Set_line(0);

	while(1)
	{
		temp_show();
	}
}

void temp_show()
{

	page_key();
	if(pageFlag == 1)
	{
		if(i == 0)
		{
			ClearScreen(0);
			i = 1;
		}
		init_welcom();		
	}
	if(pageFlag == 2)
	{
		if(z == 0)
		{
			ClearScreen(0);
			z = 1;
		}
		init_words();
		check_key();
		DS1302_Readtime();
		show_ds1302(time_data);
		if(read_temp_flag == 1)
		{
			read_temp_flag = 0;
			temp1 = read_temperature();						// 读取温度
			temperature = (float)temp1*0.0625;  	// 实际温度值
			temp = (int)temperature * 10;							// 计算温度值
		}
		if(DisFlag == 1)
		{
			DisFlag=0;
			if((temperature>0)&&(temperature<150))
			{
				show_num(1,4,32,num+16*15);									// +
				show_num(1,4,40,num+16*(temp/100));					// 温度第一位
				show_num(1,4,48,num+16*(temp%100/10));			// 温度第二位
				show_num(2,4,0,num+16*(temp%10));						// 温度第三位
	
				if(temperature<setL)	 			// 温度过低
				{
						relay_jiare=0;		// 开启升温 关闭降温
						relay_zhileng=1;
						show_ch(2,4,32,ch1+32*8);  	// 过
						show_ch(2,4,48,ch1+32*10);  // 冷
				}else if(temperature>setH) 	// 温度过高
				{
						relay_jiare=1;		// 关闭升温 开启降温
						relay_zhileng=0;
						show_ch(2,4,32,ch1+32*8);  	// 过
						show_ch(2,4,48,ch1+32*9);  // 热
				}else{
						relay_jiare=1;		// 关闭升温 关闭降温
						relay_zhileng=1;
						buzLater=0;				// 正常情况
						show_ch(2,4,32,ch1+32*6);  			// 正
						show_ch(2,4,48,ch1+32*7);  			// 常
				}
				if(buzLater>=2)				// 若非正常清零 过高过低累加 超过2秒即
				{
					buzzer=0;						// 打开蜂鸣器
					delay_ms(1000);				
				}else{				
					buzzer=1;						// 关闭蜂鸣器
				}	
			}
/******************显示温度上下限值***********************/
			show_num(1,6,16,num+16*15);									// 下限	+
			show_num(1,6,24,num+16*(setL/10));					// 温度第一位
			show_num(1,6,32,num+16*(setL%10));					// 温度第二位
			show_num(2,6,16,num+16*15);									// 上限	+
			show_num(2,6,24,num+16*(setH/10));					// 温度第一位
			show_num(2,6,32,num+16*(setH%10));					// 温度第二位

			if(SetFlag == 0)				// 查询按键设置标志
			{
				show_ch(1,6,0,ch1+32*15); // ↓
				show_ch(2,6,0,ch1+32*14); // ↑ 更新显示标志
			}else if(SetFlag == 1)								// 按键设置标志
				{
					show_ch(1,6,0,ch1+32*15); 				// ↓
					delay_ms(500);
					show_ch(1,6,0,ch1+32*16); 				// 更新显示标志(闪烁)
				}else if(SetFlag == 2)							// 查询按键设置标志
				{
					show_ch(2,6,0,ch1+32*14); 				// ↑
					delay_ms(500);
					show_ch(2,6,0,ch1+32*16);					// 更新显示标志(闪烁)
				}
				j = 0;
			}	
	}
	if(pageFlag == 3)
	{
		if(j == 0)
		{
			ClearScreen(0);
			j = 1;
		}
		init_name();
		z = 0;
	}
}
void init_timer0()
{
	TMOD = 0x61;
	TH0 = (65536-20000)/256;   // 为定时器赋初值20ms
	TL0 = (65536-20000)%256;
	TR0 = 1;	// 定时器开关打开
	ET0 = 1;	// 定时器中断打开
	EA = 1;		// 总中断打开
}

/*		定时器中断程序		*/
void timer0() interrupt 1
{
	TH0 = (65536-20000)/256;   // 为定时器赋初值20ms
	TL0 = (65536-20000)%256;
	time2ms++;
	
	if(time2ms % 10 == 0)		// 每200毫秒进行显示刷新
	{
		DisFlag=1;
		if(time2ms%50==0)	 		// 每1000毫秒进行读温度刷新
		{
			read_temp_flag=1; //读标志位置1	
		if(buzLater<200)	buzLater++;
		}
	}
}