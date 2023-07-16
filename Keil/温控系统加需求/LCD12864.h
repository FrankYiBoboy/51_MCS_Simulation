#ifndef _LCD12864_H
#define _LCD12864_H
#include <reg51.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int
#define LCD_databus P0 //���߽ӿڣ�ע��51��P0����Ҫ�����������
sbit DI = P2^3;	//DIΪ 0��дָ����״̬��1������
sbit RW = P2^4;	//1:д 0����
sbit EN = P2^5;	//ʹ��
sbit CS1 = P2^6;	//Ƭѡ1.�͵�ƽ��Ч�����������
sbit CS2 = P2^7;  //Ƭѡ2���͵�ƽ��Ч�������Ұ���

//��������
void Read_busy(); // ��æ
void write_LCD_command(uchar);  //д�����
void write_LCD_data(uchar);		// д���ݺ���
void Set_page(uchar);					// ������ʾ��ʼҳ
void Set_line(uchar);					// ������ʾ��ʼ��
void Set_column(uchar);				// ������ʾ����
void SetOnOff(uchar);					// ��ʾ���غ��� 0x3E:�� 0x3F:��
void SelectScreen(uchar);			// ѡ����Ļ
void ClearScreen(uchar);			// ����
void InitLCD();								// ��ʼ��LCD
void show_ch(uchar,uchar,uchar,uchar *);		// ��ʾ���� ������Ļλ�� ҳλ�� ��λ�� �ַ�����ʾ
void show_im(uchar,uchar,uchar,uchar *);		// ����ͬ ��ʾ32*32ͼ��
void show_num(uchar screen,uchar page,uchar column,uchar *p); // ����ͬ ��ʾ16*8����

#endif