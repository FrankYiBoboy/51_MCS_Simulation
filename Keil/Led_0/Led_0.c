#include<reg51.h>
#include<intrins.h>

#define uint unsigned int
#define uchar unsigned char
#define leds P2
	
sbit P10 = P1^0;
sbit P11 = P1^1;
sbit P12 = P1^2;
sbit P13 = P1^3;

void delay_1ms();
void delay_ms(uint n);

uchar mode1[8] = {0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,0x7F};  //ģʽһ
uchar mode2[8] = {0x7F,0xBF,0XDF,0XEF,0XF7,0XFB,0XFD,0XFE};  //ģʽ��
uchar mode3[16] = {0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,0x7F,0x7F,0xBF,0XDF,0XEF,0XF7,0XFB,0XFD,0XFE};  //ģʽ��
uchar mode4[8] = {0xFE,0xFB,0xEF,0xBF,0x7F,0xDF,0xF7,0xFD};  //ģʽ��

void main()
{	
	uchar i;
	uchar mode = 0;
	uchar key_flag = 0;
	while(!key_flag)    //�жϰ�������
	{
		if(!P10)
		{
			_nop_();  // �ӳ�һ���������� ��������
			if(!P10)
			{
				key_flag = 1;
				mode = 1;
				while(!P10);   //�ɿ���ť����ѭ�� 
			}
		}
		if(!P11)
		{
			_nop_();
			if(!P11)
			{
				key_flag = 1;
				mode = 2;
				while(!P11);
			}
		}
		if(!P12)
		{
			_nop_();
			if(!P12)
			{
				key_flag = 1;
				mode = 3;
				while(!P12);
			}
		}
		if(!P13)
		{
			_nop_();
			if(!P13)
			{
				key_flag = 1;
				mode = 4;
				while(!P13);
			}
		}	
	}
	
	while(1)            //��ˮ��
	{
		if(mode == 1)
		{
			for(i=0;i<8;i++)
			{
				P2 = mode1[i];
				delay_ms(300);
			}
		}else{
			if(mode == 2)
			{
				for(i=0;i<8;i++)
			{
				P2 = mode2[i];
				delay_ms(300);
			}
		  }else{
				if(mode == 3)
				{
					for(i=0;i<16;i++)
				{
					P2 = mode3[i];
					delay_ms(300);
				}
				}else{
					if(mode == 4)
					{
						for(i=0;i<8;i++)
					{
						P2 = mode4[i];
						delay_ms(300);
					}
					}
				}
			}
		}
	}
}



/*
��Ƭ�����辧��Ϊ12MHZ�����������Ϊ1us��
��ʱʱ��Ϊ120*8*1 = 960us������ i-- ����ʱ�� ����ʱ����Ϊ1ms��
*/
void delay_1ms()    //1ms��ʱ����
{
	uint i;
	for(i=120;i>0;i--);
}
void delay_ms(uint n)
{
	while(n--)
	{
		delay_1ms();
	}
}
