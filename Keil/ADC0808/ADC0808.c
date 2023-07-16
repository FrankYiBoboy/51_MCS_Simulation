#include <reg51.h>

#define uchar unsigned char
#define uint unsigned int

sbit START = P2^5;
sbit EOC = P2^6;
sbit OE = P2^7;
sbit CLOCK = P2^4;
sbit P23 = P2^3; // 百位
sbit P22 = P2^2; // 十位
sbit P21 = P2^1; // 个位

uchar DATE;
double BZLC=1.960784;
double DDATE;
uchar BW,SW,GW;
uchar i;


uchar code seg[10] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90}; // 数码管数字显示(共阳极)
uchar code seg_0[10] = {0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10}; // 数码管数字显示带小数点	(共阳极)
void dig_show();
void delay(uchar ms);

void init() interrupt 1 
{
	CLOCK = ~CLOCK;
}
void main()
{
	TMOD = 0x02;   // 定时器0工作方式2
	TH0 = 246;
	TL0 = 246;
	//IE = 0x82;
	TR0 = 1;
	ET0 = 1;
	EA = 1;
	TR0 = 1;
	
	while(1)
	{
		START = 0;  // 启动转换器
		START = 1;	// 复位转换器
		START = 0;	
		delay(0.1);
		//for(i=0;i<20;i++);
		while(EOC == 0)
		{
			OE = 1;          // 允许输出
		}
		DATE = P1;        // 读取P1口数据
		OE = 0;
		DDATE = DATE;
		DDATE = DDATE*BZLC;  // 利用线性转换电压值
		DATE = DDATE;
		BW = DATE/100;
		SW = (DATE%100)/10;  
		GW = DATE%10;
		delay(1);
		dig_show();
		
	}
}
void dig_show()
{
		P21 = 1;
		P0 = seg[GW];
		delay(1);
		P21 = 0;
		P22 = 1;
		P0 = seg[SW];
		delay(1);
		P22 = 0;
		P23 = 1;
		P0 = seg_0[BW];
		delay(1);
		P23 = 0;
}
void delay(uchar ms)
{
	uchar i,j;
	for(i=ms;i>0;i--)
	{
		for(j=120;j>0;j--);
	}
}