#include <reg51.h>
#include <intrins.h>

#define uchar unsigned char
#define uint unsigned int
	
char code string_1[] = "Hello";
char code string_2[] = "World!";
uchar i = 0,j = 0;
	
sbit RS = P2^0;
sbit RW = P2^1;
sbit E = P2^2;

void lcd_init();
void write_command(uchar dat); // д��ָ��
void write_data(uchar dat); // д����
void check_BF();  // ��æ�ź�
void delay(uchar ms);
void lcd_pos(uchar pos); // �趨��ʾλ��

void main()
{
	lcd_init();
	write_command(0x81);
	//lcd_pos(0x81);
	delay(1);
	while(string_1[i])
	{
		write_data(string_2[i]);
		i++;
	}
	delay(50);
	//lcd_pos(0xc0);
	write_command(0x80+0x40);
	delay(1);
	
	while(string_2[j])
	{
		write_data(string_2[j]);
		i++;
	}
	
	while(1)
	{
		
	}
}

void lcd_init()
{
	write_command(0x38); // ����ģʽ  P181
	delay(1);
	write_command(0x0c); // ������ʾ
	delay(1);
	write_command(0x06); // ��ʾ��ʽ
	delay(1);
	write_command(0x01); // ����
	delay(1);
}

void write_command(uchar dat)
{
	RS=0;RW=0;E=0;
	P0 = dat;
	E = 1;
	_nop_();  // ʹ�ܶ˴Ӹߵ�ƽ���͵�ƽִ��ָ��
	E = 0;
	delay(1);
}

void write_data(uchar dat)
{
	RS=1;RW=0;E=0;
	P0 = dat;
	E = 1;
	_nop_();
	E = 0;
	delay(1);
}

void check_BF()
{
	uchar dat;
	do
	{
		RS=0;RW=1;E=0;	
		E=1;
		dat=P0;
		_nop_();
	}while(dat&0x80);
	E = 0;
}

void delay(uchar ms)
{
	uchar i,j;
	for(i = ms;i>0;i--)
	{
		for(j=120;j>0;j--);
	}
}

void lcd_pos(uchar pos)
{
	write_command(pos | 0x80);
}