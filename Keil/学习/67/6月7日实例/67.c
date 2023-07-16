#include <reg51.h>
sbit P20 = P2^0;
sbit P21 = P2^1;
#define uchar unsigned char
#define uint unsigned int

void delay(uint n);

void main()
{
	while(1)
	{
		P20 = 0;
		delay(1000);
		P20 = 1;
		delay(1000);
	}
}

void delay(uint n)
{
	int i,j;
	for(i = n;i > 0;i--)
	{
		for(j = 120;j > 0;j--);
	}
}