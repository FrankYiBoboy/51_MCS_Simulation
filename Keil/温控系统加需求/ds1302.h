#ifndef __DS1302_H__
#define __DS1302_H__
#include <reg51.h>
#define uchar unsigned char
#define uint unsigned int
/***DS1302ʱ��оƬ****************************/
//CLK--->P3^5
//IO---->P3^6
//RES--->P3^7
/****************************/
#define OUT   0x01
#define IN    0x00

sbit CLK=P3^5;
sbit IO=P3^6;
sbit RES=P3^7;
extern uchar time_data[6];//ʱ��������

#define CLK_Reset_0  CLK=0;
#define CLK_Set_1    CLK=1;

#define IO_Reset_0   IO=0;
#define IO_Set_1     IO=1;

#define RES_Reset_0  RES=0;
#define RES_Set_1    RES=1;

/*************************/
#define Time_24_Hour    0x00    //24Сʱ��
#define Time_Start     0x00    //��ʼ��ʱ
//DS1302�Ĵ�������ָ���ʱ���ַ
#define ds1302_sec_addr   0x80       //��
#define ds1302_min_addr   0x82       //��
#define ds1302_hour_addr  0x84       //ʱ
#define ds1302_day_addr   0x86       //��
#define ds1302_month_addr 0x88       //��
#define ds1302_year_addr  0x8c       //��
/********************/
void DS1302_GPIOInit(void);
void DS1302_IO_GPIO(uchar FLAG);//����IO�ķ���
void DS1302_delay(uchar	dd);
void DS1302_Write(uchar add,uchar dat);
uchar DS1302_Read(uchar add);
void DS1302_SetTime(uchar *ad);
void DS1302_OFF(void);
void DS1302_ON(void);
void DS1302_init(uchar *time);
void DS1302_Readtime(void);



#endif
