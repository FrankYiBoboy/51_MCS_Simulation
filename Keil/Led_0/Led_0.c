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

uchar mode1[8] = {0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,0x7F};  //模式一
uchar mode2[8] = {0x7F,0xBF,0XDF,0XEF,0XF7,0XFB,0XFD,0XFE};  //模式二
uchar mode3[16] = {0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,0x7F,0x7F,0xBF,0XDF,0XEF,0XF7,0XFB,0XFD,0XFE};  //模式三
uchar mode4[8] = {0xFE,0xFB,0xEF,0xBF,0x7F,0xDF,0xF7,0xFD};  //模式四

void main()
{	
	uchar i;
	uchar mode = 0;
	uchar key_flag = 0;
	while(!key_flag)    //判断按键按下
	{
		if(!P10)
		{
			_nop_();  // 延迟一个机器周期 键盘消抖
			if(!P10)
			{
				key_flag = 1;
				mode = 1;
				while(!P10);   //松开按钮跳出循环 
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
	
	while(1)            //流水灯
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
单片机外设晶振为12MHZ，则机器周期为1us。
延时时间为120*8*1 = 960us，加上 i-- 消耗时间 则延时大致为1ms。
*/
void delay_1ms()    //1ms延时函数
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
