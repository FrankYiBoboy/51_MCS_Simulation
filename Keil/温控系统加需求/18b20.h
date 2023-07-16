#ifndef __DS18B20_H__
#define __DS18B20_H__

#include<reg51.h>     //包含头文件，一般情况不需要改动，头文件包含特殊功能寄存器的定义
#include<intrins.h>

#define uchar unsigned char
#define uint   unsigned int
/*------------------------------------------------
                    端口定义
------------------------------------------------*/
sbit DQ=P1^5;			//ds18b20 端口	
/*------------------------------------------------
                  函数声明
------------------------------------------------*/
uint read_temperature();
bit init_DS18B20();
uchar read_one_char();
void write_one_char(unsigned char dat);

#endif