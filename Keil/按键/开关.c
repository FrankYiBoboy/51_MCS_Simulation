#include<reg51.h>
#include<intrins.h>

#define uchar unsigned char;
#define uint unsigned int;
sbit P30 = P3^0;
uchar code seg[10] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90}; // 数码管数字显示(共阳极)
uint i = 0;
void display();
void main()
{
	while(1)
	{
		display();
	}
}

void display()
{
	if(!P30)
	{
		_nop_();  // 消抖处理
		while(!P30);
		P2 = seg[i];
		i++;
		if(i>=10)
		{
			i = 0;
		}
	}
}