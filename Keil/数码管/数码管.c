#include<reg51.h>

#define uchar unsigned char
#define uint unsigned int
uchar code seg[10] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90}; // �����������ʾ(������)
uchar code seg_38[10] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f}; // �����������ʾ(������)
uchar code place_code[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80}; // 8λ�������ʾλ��(δ����38������)
uchar code place_code_38[8] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07}; // 8λ�������ʾλ��(����38������)
uchar cache[8] = 0; // ���������±�λ��


void dely(uint ms);  // �������ʾ
void dig_show(); // ��ʱ
void tranfer(uchar a,s,d,f,g,h,j,k);


void main()
{
	tranfer(0,1,2,3,4,5,6,7);
	while(1)
	{
		dig_show();
	}
}

void dig_show()
{

		uint i;
		for(i=0;i<8;i++)
		{
			P3 = place_code_38[i];
			P2 = 0x00;							// ѡ��λ�ùر������ ��ֹ˲ʱ��ƽӰ��
			P2 = seg_38[cache[i]];
		}
}

void dely(uint ms)
{
	uint i,j;
	for(i=ms;i>0;i--)
	{
		for(j=120;j>0;j--);
	}
}

void tranfer(uchar a,s,d,f,g,h,j,k)
{
	cache[0] = a;
	cache[1] = s;
	cache[2] = d;
	cache[3] = f;
	cache[4] = g;
	cache[5] = h;
	cache[6] = j;
	cache[7] = k;
}