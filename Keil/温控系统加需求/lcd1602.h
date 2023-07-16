#ifndef __1602_H__
#define __1602_H__

#include<reg51.h> 
#include<intrins.h>

void DispStr(unsigned char x,unsigned char y,unsigned char *ptr);  // 从某个位置显示字符串
void DispNChar(unsigned char x,unsigned char y, unsigned char n,unsigned char *ptr); // 从某个位置显示N个字符
void LocateXY(unsigned char x,unsigned char y); // 输入显示字符位置坐标
void Disp1Char(unsigned char x,unsigned char y,unsigned char data1); // 从某个位置显示一个字符
void LcdReset(void); // LCD初始化操作
void LcdWriteCommand(unsigned char cmd,unsigned char chk); // 写指令
void LcdWriteData( unsigned char data1 );	// 写数据
void WaitForEnable(void);	// 测忙
void LcdClear(void);	// 清屏操作

#define LCD_init          LcdReset
#define LCD_Write_Char    Disp1Char
#define LCD_Write_String  DispStr
#define LCD_Clear         LcdClear
   
#endif
