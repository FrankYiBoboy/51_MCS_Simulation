#ifndef __KEY_H__
#define __KEY_H__

#include <reg51.h>
#include <delay.h>

#define uchar unsigned char 
#define uint unsigned int

sbit key1=P2^0;	 // �������Ŷ���
sbit key2=P2^1;
sbit key3=P2^2;
sbit key4=P1^7;

extern uchar SetFlag;  // ���ò�����־
extern uint setL,setH;	// �����¶�������ֵ
extern uchar pageFlag;	// ����ҳ���־


void check_key();		// �����¶������ް���
void page_key();		// ����ҳ�水��

#endif