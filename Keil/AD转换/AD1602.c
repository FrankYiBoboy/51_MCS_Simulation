#include "reg51.h"
sbit start=P3^0;
sbit eoc=P3^1;
sbit oe=P3^2;
sbit RS=P3^3;
sbit RW=P3^4;
sbit E=P3^5;
unsigned int vol=0;
unsigned char arr[]={"0123456789"};
unsigned char str[]={"VOLTAGE:"};

void delay(unsigned int n)//��ʱ����
{
  unsigned int i,j;
	for(i=0;i<n;i++)
	{
	  for(j=0;j<120;j++);
	}
}

void adc()
{
  start=0; // �ر�A/Dת�������ź�
  start=1; // ��A/Dת�������ź�
  delay(5);
  start=0; // �ر�A/Dת�������ź�
  while(eoc!=1);//�ж�A/Dת�������ź��Ƿ�Ϊ1��1��ת����ɣ����
	oe=1;   //������������ź�
	vol=P2;//��ȡ���ݽ��
	oe=0;//������������ź�
}

void writecom(unsigned char com)//д�����
{
  RS=0; //  RS:����/����ѡ���
	RW=0;//  R/W :��/дѡ��� 
	E=0; //  ʹ�ܶ�:�½�����Ч
	delay(5);
	P1=com;
	E=1;
	E=0;
}

void writedat(unsigned char dat)//д���ݺ���
{
  RS=1; //  RS:����/����ѡ���
	RW=0;//  R/W :��/дѡ��� 
	E=0; //  ʹ�ܶ�:�½�����Ч
	delay(5);
	P1=dat;
	E=1;
	E=0;
}

void initlcd()//��ʼ��LCD1602
{
  writecom(0x38); //0x38������16��2��ʾ
	writecom(0x0c); //0x0C�����ÿ���ʾ������ʾ���
	writecom(0x06); //0x06��дһ���ַ����ַָ���1
	writecom(0x01); //0x01����ʾ��0������ָ����0
}

void display()//��ʾ����
{
	unsigned int i=0;
  unsigned char temp0=0,temp1=0,temp2=0;
	vol=(vol*100)/51; //  255/5=51
	temp0=vol/100;
	temp1=(vol%100)/10;
	temp2=vol%10;
	
  writecom(0x80);//0x80��LCD��һ�е���ʼ��ַ
	delay(5);
	for(i=0;i<8;i++)//��ʾ�ַ��� VOLTAGE:
	{
	  writedat(str[i]);
		delay(5);
	}
	
	writecom(0x80+0x40+8);// 0x80+0x40+8 LCD�ڶ��е���ʼ��ַ+8���ַ�
  delay(5);
  writedat(arr[temp0]);
  delay(5);
	writedat('.');
	delay(5);
	writedat(arr[temp1]);
  delay(5);
  writedat(arr[temp2]);
  delay(5);
  writedat('V');
  delay(5);
}

void main()
{
	initlcd();
  while(1)
	{
	  adc();
		display();
	}
}