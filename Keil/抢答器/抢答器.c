#include <reg51.h>

#define uchar unsigned char
#define uint unsigned int
uchar code seg[10] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
uchar code place_code[8]= {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
uchar index[8] = 0;

void transfer(uint count,uchar order[]);  //改变数码管索引
void delay_ms(uint ms); //延时函数
void show();    //显示函数

void main()
{
	uchar index_0[8] = {9,1,2,6,5,6,7,8};  //数码管依次显示数字
	transfer(8,index_0);
	while(1)
	{
		show();
	}
}

void delay_ms(uint ms)
{
	uint i;
	for(;ms>0;ms--)
	{
		for(i=0;i<120;i++);
	}
}
void transfer(uint count,uchar order[])
{
	uint i;
	for(i=0;i<count;i++)
	{
		index[i] = *(order+i);
	}	
}
void show()
{
	uchar i = 2;
	for(i=0;i<8;i++)
	{
		P3 = place_code[i];
		P2 = 0xff;
		P2 = seg[index[i]];
	}	
}