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

void delay(unsigned int n)//延时函数
{
  unsigned int i,j;
	for(i=0;i<n;i++)
	{
	  for(j=0;j<120;j++);
	}
}

void adc()
{
  start=0; // 关闭A/D转换启动信号
  start=1; // 打开A/D转换启动信号
  delay(5);
  start=0; // 关闭A/D转换启动信号
  while(eoc!=1);//判断A/D转换结束信号是否为1，1则转换完成，输出
	oe=1;   //数据输出允许信号
	vol=P2;//读取数据结果
	oe=0;//数据输出允许信号
}

void writecom(unsigned char com)//写命令函数
{
  RS=0; //  RS:数据/命令选择端
	RW=0;//  R/W :读/写选择端 
	E=0; //  使能端:下降沿有效
	delay(5);
	P1=com;
	E=1;
	E=0;
}

void writedat(unsigned char dat)//写数据函数
{
  RS=1; //  RS:数据/命令选择端
	RW=0;//  R/W :读/写选择端 
	E=0; //  使能端:下降沿有效
	delay(5);
	P1=dat;
	E=1;
	E=0;
}

void initlcd()//初始化LCD1602
{
  writecom(0x38); //0x38；设置16×2显示
	writecom(0x0c); //0x0C：设置开显示，不显示光标
	writecom(0x06); //0x06：写一个字符后地址指针加1
	writecom(0x01); //0x01：显示清0，数据指针清0
}

void display()//显示函数
{
	unsigned int i=0;
  unsigned char temp0=0,temp1=0,temp2=0;
	vol=(vol*100)/51; //  255/5=51
	temp0=vol/100;
	temp1=(vol%100)/10;
	temp2=vol%10;
	
  writecom(0x80);//0x80：LCD第一行的起始地址
	delay(5);
	for(i=0;i<8;i++)//显示字符串 VOLTAGE:
	{
	  writedat(str[i]);
		delay(5);
	}
	
	writecom(0x80+0x40+8);// 0x80+0x40+8 LCD第二行的起始地址+8个字符
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