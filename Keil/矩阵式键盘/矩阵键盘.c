#include <reg51.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int
	
uchar code seg[10] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90}; // 数码管数字显示(共阳极)
uchar code seg_38[10] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f}; // 数码管数字显示(共阴极)
uchar code place_code[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80}; // 8位数码管显示位置(未采用38译码器)
uchar code place_code_38[8] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07}; // 8位数码管显示位置(采用38译码器)
uchar cache[8] = 0; // 缓存数组下标位置
uchar num = 0;
void key_scan();   // 矩阵键盘扫描
void dely(uint ms);  // 数码管显示
void dig_show(); // 延时
void tranfer(uchar a,s,d,f,g,h,j,k);


void main()
{
	
	while(1)
	{
		
		key_scan();
		tranfer(0,0,0,0,0,0,num / 10,num % 10);
		dig_show();

	}
}

void dig_show()
{

		uint i;
		for(i=0;i<8;i++)
		{
			P3 = place_code[i];
			P2 = 0xff;							// 选中位置关闭数码管 防止瞬时电平影响
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

void key_scan()
{
	uchar i,temp,num = 0;
	for(i=0;i<4;i++)
	{
		P1 = _crol_(0xfe,i);
		temp = P1;
		temp =temp & 0xf0;
		if(temp != 0xf0)
		{
			_nop_();
			temp = P1;
			temp =temp & 0xf0;
			if(temp != 0xf0)
			{
				temp = P1;
				switch(temp)
				{
					case 0xee:num = 0;break;
					case 0xde:num = 1;break;
					case 0xbe:num = 2;break;
					case 0x7e:num = 3;break;
					case 0xed:num = 4;break;
					case 0xdd:num = 5;break;
					case 0xbd:num = 6;break;
					case 0x7d:num = 7;break;
					case 0xeb:num = 8;break;
					case 0xdb:num = 9;break;
					case 0xbb:num = 10;break;
					case 0x7b:num = 11;break;
					case 0xe7:num = 12;break;
					case 0xd7:num = 13;break;
					case 0xb7:num = 14;break;
					case 0x77:num = 15;break;
					default:break;
				}
				while((temp & 0xf0)!=0xf0)
				{
					temp = P1;
					temp = temp&0xf0;
				}
			}
		}
	}
}