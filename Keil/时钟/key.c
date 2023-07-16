#include <reg51.h>

#define uchar unsigned char 
#define uint unsigned int
bit k_flag=0;
uchar hour,min,s;
sbit P10=P1^0;
sbit P11=P1^1;
sbit P12=P1^2;
sbit P13=P1^3;
sbit P14=P1^4;
sbit P15=P1^5;
sbit P16=P1^6;
sbit P17=P1^7;
uchar key_num=0;
uchar code seg[11]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xbf};	
uchar code place_code[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
uchar code place_code1[8]={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07};
uchar cache[8]={0,0,0,0,0,0,0,0};
void tranfer(uchar a,s,d,f,g,h,j,k)
{
	cache[0]=a;
	cache[1]=s;
	cache[2]=d;
	cache[3]=f;
	cache[4]=g;
	cache[5]=h;
	cache[6]=j;
	cache[7]=k;
}
void delay(uint ms)
{
	uint i,j;
	for(i=ms;i>0;i--)
		for(j=120;j>0;j--);
}

void nixie_show()
{
	char i;
	for(i=0;i<8;i++)
	{
		P3=place_code[i];
		P2=0x00;
		P2=seg[cache[i]];
		delay(1);
	}
}
void key_scan()
{
	char kx=0,ky=0;
	if(k_flag==0)
	{
		P1=0x0f;
		if(P10==0||P11==0||P12==0||P13==0)
		{
			if(P10==0) kx=-1;
			if(P11==0) kx=3;
			if(P12==0) kx=7;
			if(P13==0) kx=11;
		}
		P1=0xf0;//
		if(P14==0||P15==0||P16==0||P17==0)
		{
			if(P14==0) ky=4;
			if(P15==0) ky=3;
			if(P16==0) ky=2;
			if(P17==0) ky=1;
		}
		if(ky==0)  k_flag=0;
		else
		{
			key_num=kx+ky;
			k_flag=1;
		}
	}
}


void main()
{
	while(1)
	{	
		key_scan();
		if(k_flag==1)
		{
			k_flag=0;
		}
		nixie_show();
	}
}