#include <reg51.h>
#include <intrins.h>
#define uchar unsigned char 
#define uint unsigned int
uchar code column[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};
uchar code line[]={0x00,0x00,0x38,0x28,0xff,0x28,0x38,0x00};
void delay(int ms);

void main()
{
	while(1)
	{

		uint i;
		for(i=0;i<8;i++)
		{
			P2 = column[i];
			P3 = line[i];
			delay(1);
			P2 = 0xff;  
			P3 = 0x00;
		}
	}
}

void delay(int ms)
{
	int i,j;
	for(i=ms;i>0;i--)
	{
		for(j=120;j>0;j--);
	}
}