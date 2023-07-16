#ifndef __KEY_H__
#define __KEY_H__

#include <reg51.h>
#include <delay.h>

#define uchar unsigned char 
#define uint unsigned int

sbit key1=P2^0;	 // 按键引脚定义
sbit key2=P2^1;
sbit key3=P2^2;
sbit key4=P1^7;

extern uchar SetFlag;  // 设置参数标志
extern uint setL,setH;	// 设置温度上下限值
extern uchar pageFlag;	// 设置页面标志


void check_key();		// 调整温度上下限按键
void page_key();		// 调整页面按键

#endif