#include <18b20.h>
#include <delay.h>

#define uchar unsigned char
#define uint unsigned int


	
bit init_DS18B20()
{
	bit dat=0;
	DQ = 1;    //DQ复位
	delay_us(5);   //稍做延时
	DQ = 0;         //单片机将DQ拉低
	delay_us(200); //精确延时 大于 480us 小于960us
	delay_us(200);
	DQ = 1;        //拉高总线
	delay_us(50); //15~60us 后 接收60-240us的存在脉冲
	dat=DQ;        //如果dat=0则初始化成功, dat=1则初始化失败
	delay_us(25); //稍作延时返回
	return dat;
}

/*------------------------------------------------
                    读取一个字节
------------------------------------------------*/
uchar read_one_char()
{
	uchar i=0;
	uchar dat = 0;
	for (i=8;i>0;i--)
 {
		DQ = 0; // 拉低总线
		dat>>=1; // 每读取数据 循环左移
		DQ = 1; // 拉高总线
		if(DQ)
		dat|=0x80; // 或运算
		delay_us(25);
 }
	return(dat);
}

/*------------------------------------------------
                    写入一个字节
------------------------------------------------*/
void write_one_char(uchar dat)
{
 uchar i=0;
 for (i=8;i>0;i--)
 {
  DQ = 0;
  DQ = dat&0x01;
  delay_us(25);
  DQ = 1;
  dat>>=1;
 }
delay_us(25);
}

/*------------------------------------------------
                    读取温度
------------------------------------------------*/
uint read_temperature()
{
	uchar a=0;
	uint b=0;
	uint temp=0;
	init_DS18B20();
	write_one_char(0xCC); // 跳过读序号列号的操作
	write_one_char(0x44); // 启动温度转换
	delay_ms(10);
	init_DS18B20();
	write_one_char(0xCC); //跳过读序号列号的操作 
	write_one_char(0xBE); //读取温度寄存器等（共可读9个寄存器） 前两个就是温度
	a=read_one_char();   //低位
	b=read_one_char();   //高位

	b<<=8;
	temp=a+b;

	return temp;
}