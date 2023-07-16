#include <reg51.h>
#include <intrins.h>

#define uchar unsigned char
#define uint unsigned int
	
uint time;
bit flag = 0;     // 判断是否执行完一秒
bit k_flag = 0;	  // 判断按键是否按下
char key_num = 0;
char key_x=0;
char key_y=0;
uchar s,min,hour;

sbit P10=P1^0;
sbit P11=P1^1;
sbit P12=P1^2;
sbit P13=P1^3;
sbit P14=P1^4;
sbit P15=P1^5;
sbit P16=P1^6;
sbit P17=P1^7;

uchar code seg[11] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xbf}; // 数码管数字显示(共阳极)
uchar code place_code[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80}; // 8位数码管显示位置(未采用38译码器)
uchar code place_code_38[8] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07}; // 8位数码管显示位置(采用38译码器)

uchar cache[8] = 0; // 缓存数组下标位置
void key_scan();   // 矩阵键盘扫描
void dely(uint ms);  // 延时
void dig_show(); // 数码管显示
void tranfer(uchar a,s,d,f,g,h,j,k);
void init_timer0(); // 定时中断初始化
void Delay1us(); // 延时1us
void clock();  // 数码电子时钟
void time_set(uchar H,M,S);  // 设置时钟初始值

void main()
{
	time_set(23,59,57);
	init_timer0();
	
	while(1)
	{			
		if(k_flag==1)
		{
			k_flag=0;
		}
		
		if(flag == 1)
		{
			clock();
			flag=0;
		}
	}
}

void dig_show()
{

		uint i;
		for(i=0;i<8;i++)
		{
			P0 = place_code_38[i];
			P2 = 0xff;			// 关闭数码管显示 防止瞬时电平影响			
			P2 = seg[cache[i]];
			Delay1us();  // 延时1us 防止数码管电平转换过快
		}
}

void dely(uint ms)
{
	uint i,j;
	for(i=ms;i>0;i--)
	{
		for(j=120;j>0;j--);
	}
}

void tranfer(uchar a,s,d,f,g,h,j,k)
{
	cache[0] = a;
	cache[1] = s;
	cache[2] = d;
	cache[3] = f;
	cache[4] = g;
	cache[5] = h;
	cache[6] = j;
	cache[7] = k;
}

void key_scan()
{
	if(k_flag==0)
	{
		P1=0x0f;
		if(P10==0||P11==0||P12==0||P13==0)
		{
			if(P10==0) key_x=-1;
			if(P11==0) key_x=3;
			if(P12==0) key_x=7;
			if(P13==0) key_x=11;
		}
		P1=0xf0;
		if(P14==0||P15==0||P16==0||P17==0)
		{
			if(P14==0) key_y=4;
			if(P15==0) key_y=3;
			if(P16==0) key_y=2;
			if(P17==0) key_y=1;
		}
		if(key_y==0)  k_flag=0;
		else
		{
			key_num=key_x+key_y;
			if(key_num == 1)
			{
				time_set(22,59,58);
			}
			k_flag=1;
		}
	}
}

void Delay1us()		//@12.000MHz
{
	_nop_();
	_nop_();
	_nop_();
	_nop_();
}

void init_timer0()
{
	TMOD = 0x01;
	TH0 = (65536-1000) / 256;
	TL0 = (65536-1000) % 256;
	TR0 = 1;
	ET0 = 1;
	EA = 1;
}
void timer0() interrupt 1
{
	TH0 = (65536-1000) / 256;
	TL0 = (65536-1000) % 256;
	
	if(flag == 0)
	{
		time++;
		if(time>=1000)
		{
			time = 0;
			flag = 1;
		}
	}
	key_scan();
	dig_show();	
}
void time_set(uchar H,M,S)
{
	hour = H;
	min = M;
	s = S;
}

void clock()   
{
	s++;
	if(s>=60)
	{
		s = 0;
		min++;
		if(min>=60)
		{
			min = 0;
			hour++;
			if(hour>=24)
			{
				hour = 0;
			}
		}
	}
	tranfer(hour/10,hour%10,10,min/10,min%10,10,s/10,s%10);
}