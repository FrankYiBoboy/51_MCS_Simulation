#ifndef __1602_H__
#define __1602_H__

#include<reg51.h> 
#include<intrins.h>

void DispStr(unsigned char x,unsigned char y,unsigned char *ptr);  // ��ĳ��λ����ʾ�ַ���
void DispNChar(unsigned char x,unsigned char y, unsigned char n,unsigned char *ptr); // ��ĳ��λ����ʾN���ַ�
void LocateXY(unsigned char x,unsigned char y); // ������ʾ�ַ�λ������
void Disp1Char(unsigned char x,unsigned char y,unsigned char data1); // ��ĳ��λ����ʾһ���ַ�
void LcdReset(void); // LCD��ʼ������
void LcdWriteCommand(unsigned char cmd,unsigned char chk); // дָ��
void LcdWriteData( unsigned char data1 );	// д����
void WaitForEnable(void);	// ��æ
void LcdClear(void);	// ��������

#define LCD_init          LcdReset
#define LCD_Write_Char    Disp1Char
#define LCD_Write_String  DispStr
#define LCD_Clear         LcdClear
   
#endif
