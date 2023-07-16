#include"ds1302.h"

  /*****************************************
 * ��������void DS1302_delay(u8 dd)
 * ����  ������ʱ
 * ����  ��
 * ���  ����
 * ����  ��
 *************************************/
void DS1302_delay(uchar dd)
{
    uchar i;
    for(;dd>0;dd--)
  for(i=110;i>0;i--);
}

  /*****************************************
 * ��������void DS1302_Write(uchar add,uchar dat)
 * ����  ��DS1302дָ�������
*  ����  ��add:���͵�ַ��dat����������
 * ���  ����
 * ����  ��
 *************************************/
 void DS1302_Write(uchar add,uchar dat)
 {
 uchar i,temp1,temp2;
 temp1=add;
 temp2=dat;
 RES_Set_1;//RET=1;
//���͵�ַ
for(i=0;i<8;i++)
 {
        if(temp1&0x01)
         {IO_Set_1;  }     //IO=1;
        else
        { IO_Reset_0;}   //�IIO=0;
        temp1=temp1>>1;
        CLK_Set_1;            //CLK=1;
        DS1302_delay(2);
        CLK_Reset_0;    //CLK=0;
  }

//��������
for(i=0;i<8;i++)
    {
        /*IO=(temp2>>i)&0x01;��һ������������ε�����  */
        if(temp2&0x01)
         {IO_Set_1;  }     //IO=1;
        else
         { IO_Reset_0;}    //�IIO=0;
            temp2=temp2>>1;
            CLK_Set_1;            //CLK=1;
            DS1302_delay(2);
            CLK_Reset_0;    //CLK=0;
    }
RES_Reset_0;// RET=0;
 }




/*****************************************
 * ��������uchar DS1302_Read(uchar add)
 * ����  ��DS1302������
 *  ����  ��add:�������ڵ�ַ
 * ���  ��
 * ����  ��
 *************************************/
uchar DS1302_Read(uchar add)
{
  uchar i,suf,temp,mm,nn,value;
   temp=add;
   RES_Set_1;//RET=1;
    //д��ַ
  for(i=0;i<8;i++)
      {
       if(temp&0x01)
       {IO_Set_1;  }     //IO=1;
      else
         { IO_Reset_0;}    //IO=0;
      temp=temp>>1;
        CLK_Set_1;            //CLK=1;
        DS1302_delay(2);
        CLK_Reset_0;    //CLK=0;
      }
 //������

  for(i=0;i<8;i++)
    {
     suf=suf>>1;//�����ݱ���
     if(IO)    //IO=1
     {
         suf=suf|0x80;
     }
     else     //IO=0
     {
     suf=suf&0x7f;
     }

        CLK_Set_1;            //CLK=1;
        DS1302_delay(2);
        CLK_Reset_0;    //CLK=0;
    }
    RES_Reset_0;    // RET=0;

//���ݴ���ת��ʮ����
mm=suf/16;
nn=suf%16;
value=mm*10+nn;
return value;
}
/*****************************************
 * ��������void DS1302_SetTime(uchar *ad)
 * ����  ��DS1302 д������ʱ��
 *  ����  ��add:�������ڵ�ַ
 * ���  ��
 * ����  ��
 *************************************/
void DS1302_SetTime(uchar *ad)
  {
   DS1302_Write(0x8e,0x00);   //WP=0 ��������д��DS1302
/**********���¶�ʱ����ĳ�ʼ��*************/
        DS1302_Write(ds1302_sec_addr,ad[5]/10*16+ad[5]%10);  //��
        DS1302_Write(ds1302_min_addr,ad[4]/10*16+ad[4]%10);   //��
        DS1302_Write(ds1302_hour_addr,ad[3]/10*16+ad[3]%10);   //ʱ
      /**********���¶������յĳ�ʼ��*************/
     DS1302_Write(ds1302_day_addr,ad[2]/10*16+ad[2]%10);
   DS1302_Write(ds1302_month_addr,ad[1]/10*16+ad[1]%10);
      DS1302_Write(ds1302_year_addr,ad[0]/10*16+ad[0]%10);

     DS1302_Write(0x8e,0x80);   //0x8e�����ֽڵ�ַ,bit7=WP WP=1 ��ֹ����д��DS1302
  }


/*****************************************
 * �������� void DS1302_OFF(void)
 * ����  ��DS1302ʱ���ֹ��ʱ
 *  ����  ��
 * ���  ��
 * ����  ��
 *************************************/
  void DS1302_OFF(void)
  {
   uchar temp;
   temp=DS1302_Read(0x81);//��ȡ���ַʱ��
   DS1302_Write(0x8e,0x00);//WP=0 ��������д��DS1302
   temp=temp|(1<<7);
   DS1302_Write(0x80,temp);//WP=1 ��ֹ����д��DS1302

  }
/*****************************************
 * �������� void DS1302_ON(void)
 * ����  ��DS1302ʱ�俪ʼ���У���ʱ
 *  ����  ��
 * ���  ��
 * ����  ��
 *************************************/
  void DS1302_ON(void)
  {
   uchar temp;
   temp=DS1302_Read(0x81);
   DS1302_Write(0x8e,0x00);//WP=0 ��������д��DS1302
   temp=temp|(0<<7);
   DS1302_Write(0x80,temp);//WP=0 ��������д��DS1302

  }






 /*****************************************
 * ��������void DS1302_init(uchar *time)
 * ����  ��    DS1302��ʼ��
 * ����  ����
 * ���  ����
* ����  ��
 *************************************/
void DS1302_init(uchar *time)
{
  RES_Reset_0; //RET=0;
  CLK_Reset_0;// CLK=0;
  DS1302_Write(0x8e,0x00);//WP=0 ��������д��DS1302
	DS1302_SetTime(time);//�������ó�ʼʱ��
}
 /*****************************************
 * ��������void DS1302_Readtime(void)
 * ����  ��    DS1302ʱ�����
 * ����  ����
 * ���  ����
* ����  ��
 *************************************/
void DS1302_Readtime(void)//
{
			time_data[0]=DS1302_Read( 0x8D);
			time_data[1]=DS1302_Read( 0x89);
			time_data[2]=DS1302_Read( 0x87);
			time_data[3]=DS1302_Read( 0x85);
			time_data[4]=DS1302_Read( 0x83);
			time_data[5]=DS1302_Read( 0x81);
}
