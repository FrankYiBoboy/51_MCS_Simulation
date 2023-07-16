#include <reg51.h>
#define uchar unsigned char
#define uint unsigned int
sbit P32 = P3^2;
sbit P33 = P3^3;
uchar code seg[10] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};  // 共阳极数码管显示
uchar i = 0;

void init_int0();
void init_int1();

void main()
{
	while(1)
	{
		init_int0();
		init_int1();
		if(i>=10)
		{
			i = 0;
		}
		P2 = seg[i];

	}
}

void init_int0()
{
	IT0 = 0;	
	EX0 = 1;
	EA = 1;
	
}
void init_int1()
{
	IT1 = 0;	
	EX1 = 1;
	EA = 1;
}
void int0() interrupt 0
{
	i++;
	while(P32 == 0);
}
void int1() interrupt 2
{
	if(i==0)
	{
	i = 10;
	}
	i--;
	while(P33 == 0);

}