#include<reg51.h>
#define uchar unsigned char
#define uint unsigned int
uint time;
bit flag = 0,nflag = 0;  // ��ʱ������״̬
sbit P20 = P2^0;
sbit P21 = P2^1;
void init_timer0();   

void main()
{
	init_timer0();
	while(1)
	{
		P20 = flag;
		P21 = nflag;
	}
}
void init_timer0()
{
	
	TMOD = 0x61;  // 0x01��ʱ��0����16λ������ʽ 0x61���ü�����1 8λ�Զ���װ�ع�����ʽ
	TH0 = (65536-50000)/256;
	TL0 = (65536-50000)%256;
	TR0 = 1;
	ET0 = 1;
	EA = 1;
	TH1 = 256-3;
	TL1 = 256-3;
	TR1 = 1;
	ET1 = 1;
	
}
void timer0() interrupt 1
{
	TH0 = (65536-50000)/256;
	TL0 = (65536-50000)%256;
	time++;
	if(time >= 10)
	{
		time = 0;
		flag = !flag;
	}
}
void counter1() interrupt 3
{
	nflag = !nflag;
}