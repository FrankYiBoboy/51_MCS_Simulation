#include<reg51.h>

#define uchar unsigned char
#define uint unsigned int
	
uchar code seg[10] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90}; // �����������ʾ(������)
uchar code place_code[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80}; // 8λ�������ʾλ��(δ����38������)
uchar cache[8] = 0; // ���������±�λ��


void dely(uint ms);  // ��ʱ
void dig_show(); // �������ʾ
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

		uchar i;
		for(i=0;i<8;i++)
		{
			P3 = place_code[i];
			P2 = 0xff;							// ѡ��λ�ùر������ ��ֹ˲ʱ��ƽӰ��
			P2 = seg[cache[i]];
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