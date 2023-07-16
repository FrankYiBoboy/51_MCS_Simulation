#ifndef _LCD12864_H
#define _LCD12864_H
#include <reg51.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int
#define LCD_databus P0 //总线接口，注意51的P0口需要外接上拉电阻
sbit DI = P2^3;	//DI为 0：写指令或读状态，1：数据
sbit RW = P2^4;	//1:写 0：读
sbit EN = P2^5;	//使能
sbit CS1 = P2^6;	//片选1.低电平有效，控制左半屏
sbit CS2 = P2^7;  //片选2，低电平有效，控制右半屏

//声明函数
void Read_busy(); // 测忙
void write_LCD_command(uchar);  //写命令函数
void write_LCD_data(uchar);		// 写数据函数
void Set_page(uchar);					// 设置显示起始页
void Set_line(uchar);					// 设置显示起始行
void Set_column(uchar);				// 设置显示的列
void SetOnOff(uchar);					// 显示开关函数 0x3E:关 0x3F:开
void SelectScreen(uchar);			// 选择屏幕
void ClearScreen(uchar);			// 清屏
void InitLCD();								// 初始化LCD
void show_ch(uchar,uchar,uchar,uchar *);		// 显示汉字 输入屏幕位置 页位置 列位置 字符串显示
void show_im(uchar,uchar,uchar,uchar *);		// 与上同 显示32*32图像
void show_num(uchar screen,uchar page,uchar column,uchar *p); // 与上同 显示16*8数字

#endif