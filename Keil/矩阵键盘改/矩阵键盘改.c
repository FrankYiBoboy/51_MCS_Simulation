#include <reg51.h>

#define uchar unsigned char
#define uint unsigned int
bit k_flag = 0;	
char key_num = 0;
char kx=0,ky=0;
sbit P10 = P1^0;
sbit P11 = P1^1;
sbit P12 = P1^2;
sbit P13 = P1^3;
sbit P14 = P1^4;
sbit P15 = P1^5;
sbit P16 = P1^6;
sbit P17 = P1^7;
uchar code seg[10] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90}; // 数码管数字显示(共阳极)
uchar code place_code[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80}; // 8位数码管显示位置(未采用38译码器)

uchar cache[8] = 0; // 缓存数组下标位置
void key_scan();   // 矩阵键盘扫描
void dely(uint ms);  // 延时
void dig_show(); // 数码管显示
void tranfer(uchar a,s,d,f,g,h,j,k);


void main()
{	
	while(1)
	{	
		key_scan();
		if(k_flag == 1)
		{
			k_flag = 0;
		}
		tranfer(0,0,0,0,0,0,key_num / 10,key_num % 10);
		dig_show();

	}
}

void dig_show()
{
		uint i;
		for(i=0;i<8;i++)
		{
			P3 = place_code[i];
			P2 = 0xff;							// 选中位置关闭数码管 防止瞬时电平影响
			P2 = seg[cache[i]];
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