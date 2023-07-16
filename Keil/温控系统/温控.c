#include <reg51.h>
#include <18b20.h>
#include <delay.h>
#include <lcd1602.h>
#include <stdio.h>


#define uchar unsigned char
#define uint unsigned int
	
sbit key1=P2^0;	 // 按键引脚定义
sbit key2=P2^1;
sbit key3=P2^2;

sbit relay_jiare=P1^0;  // 加热制冷与蜂鸣器引脚定义
sbit relay_zhileng=P1^1;
sbit buzzer=P1^4;

uint setL = 25;  		// 设置温度下限
uint setH = 30; 		// 设置温度上限
uchar DisFlag = 0;  // 更新显示标志
uchar SetFlag = 0;  // 设置参数标志

uint time2ms=0;		// 定时计数
uint buzLater=0;  // 蜂鸣器累加检测

uint temp1;								// 读取温度初始值
float temperature = 0;				// 实际温度值
uchar read_temp_flag = 1;			// 定义读温度标志

char dis0[16];			//定义显示区域临时存储数组
char dis1[16];			//定义显示区域临时存储数组

void check_key();   // 按键检查
void init_timer0();   // 定时器初始化
void dig_show(); 		// 显示


void main()
{
	relay_jiare = 1;
	relay_zhileng = 1;
	buzzer = 1;
	
	init_timer0(); 		// 初始化定时器
	LCD_init();				// 初始化LCD
	delay_ms(100);
	LCD_Clear();
		
	while(1)
	{
		dig_show();
	}
}

void dig_show()
{
	check_key();
	if(read_temp_flag == 1)
	{
		read_temp_flag = 0;
		temp1 = read_temperature();						// 读取温度
		temperature = (float)temp1*0.0625;  	// 实际温度值
	}
	if(DisFlag == 1)
	{
		DisFlag=0;
		if((temperature>0)&&(temperature<150))
		{
			sprintf(dis0,"Temp:%4.1f C",temperature);			// 将温度值存储进暂存显示数组
			LCD_Write_String(0,0,dis0);										// 显示第一行第一位
			LCD_Write_Char(9,0,0xdf);											// 显示温度左上角°
			
			if(temperature<setL)	 			// 温度过低
			{
					relay_jiare=0;		// 开启升温 关闭降温
					relay_zhileng=1;	
			}else if(temperature>setH) 	// 温度过高
			{
					relay_jiare=1;		// 关闭升温 开启降温
					relay_zhileng=0;
			}else{
					relay_jiare=1;		// 关闭升温 关闭降温
					relay_zhileng=1;
					buzLater=0;				// 正常情况
			}
			if(buzLater>=2)				// 若非正常清零 过高过低累加 超过2秒即
			{
				buzzer=0;						// 打开蜂鸣器
				delay_ms(1000);				
			}else{				
				buzzer=1;						// 关闭蜂鸣器
			}	
		}
		
		sprintf(dis1," %02d-- %02d       ",setL,setH);		// 将温度范围存储暂定显示数组
		LCD_Write_String(0,1,dis1);				// 初始化显示 		
		if(SetFlag == 0)			// 查询按键设置标志
		{
			LCD_Write_Char(0,1,' ');
			LCD_Write_Char(5,1,' ');			// 更新显示标志
		}else if(SetFlag == 1)//按键设置标志
			{
				LCD_Write_Char(0,1,'W');
				LCD_Write_Char(5,1,' ');		// 更新显示标志(闪烁)
			}else if(SetFlag == 2)	// 查询按键设置标志
			{
				LCD_Write_Char(0,1,' ');
				LCD_Write_Char(5,1,'W');		// 更新显示标志
			}	
	}	
}

void check_key()
{
	uchar rekey = 0;
	if((key1==0)||(key2==0)||(key3==0))
	{
		delay_ms(10);
		if(rekey==0)	
		{
			if(key1==0)    // 检测按键1是否按下
			{
				rekey=1;
				SetFlag++;	// 设置参数标志
				if(SetFlag >= 3) SetFlag = 0;  		// 设置1,设置2
			}	
			else if(key2 == 0)	//   检测按键2是否按下
			{
				rekey=1;
				if(SetFlag == 1)      		// 处于设置1
				{
					if(setL > 0 )
						{
						setL = setL-1;
						}
				}
				else if(SetFlag == 2)			// 处于设置2
				{
					if(setH > 0)
					{
					setH = setH-1;
					}
				}						
			}else if(key3==0)			// 检测按键3是否按下
			{
				rekey=1;
				if(SetFlag == 1)      // 处于设置1
				{
					if(setL < 99 )
					{
					setL=setL+1;
					}
				}
				else if(SetFlag==2)	// 处于设置2
				{
					if(setH < 99 )
					{
					setH=setH+1;
					}
				}				
			}
		}
	}else{
		rekey = 0; 	// 防止重新检测到按键
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