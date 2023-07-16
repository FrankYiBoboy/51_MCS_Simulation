#include <reg51.h>

#define uint unsigned int
#define uchar unsigned char

sbit P20 = P2^0;
uchar dat;
bit flag = 0;
void send();
void init()   // ���ڳ�ʼ��
{
	SCON = 0x50; 	// ���ڣ�ģʽ1
	TMOD = 0x20;  // ��ʱ��1 ģʽ2
	TH1 = 0xfd;
	TL1 = 0xfd;
	TR1 = 1;
	ES = 1;
	EA = 1;
}

void main()
{
	init();
	while(1)
	{
		if(flag == 1)
		{
			send();
			if(dat == '0')
			{
				P20 = 0;
			}else{
				P20 = 1;
			}
			flag = 0;
		}
	}
}
void send()
{
	SBUF = dat;
	while(TI == 0);
	TI = 0;
}

void uart() interrupt 4
{
	if(RI)
	{
		dat = SBUF;
		flag = 1;
		RI = 0;
	}
}

