#include <reg51.h>
#include <intrins.h>

#define unchar unsigned char
#define unint unsigned int
unchar code seg_xust[8] = {0x00,0x10,0x00,0x01,0x00,0x04,0x02,0x02};  // —ß∫≈
unchar code seg[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};  // ledµ∆
unchar code seg_key[8] = {0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f}; // º¸≈Ã…®√Ë
unchar key_flag = 0;
void key_scan_test();

void delay_1ms();
void delay_ms(unint n);
void dig_show()
{
	unchar i = 0;
	P2 = seg[3];
	i =key_scan();
	P2 = seg[1];
	key_flag = 0;
}
void main()
{
	while(1)
	{
		
//		key_scan_test();
//		key_flag =0;
		unchar i;
		for(i=0;i<8;i++)
		{
			
			P2 = seg_xust[i];
			delay_ms(1000);
		}
	}
}

void delay_1ms()    //1ms—” ±∫Ø ˝
{
	unint i;
	for(i=120;i>0;i--);
}
void delay_ms(unint n)
{
	while(n--)
	{
		delay_1ms();
	}
} 
void key_scan_test()
{
	
	while(key_flag == 0)
	{	
	if(P1!=0xff)
		 {
				_nop_();
			 if(P1!=0xff)
			 {
					switch(P1)
					{
						case 0xfe:P2 = seg_key[0];break;
						case 0xfd:P2 = seg_key[1];break;
						case 0xfb:P2 = seg_key[2];break;
						case 0xf7:P2 = seg_key[3];break;
						case 0xef:P2 = seg_key[4];break;
						case 0xdf:P2 = seg_key[5];break;
						case 0xbf:P2 = seg_key[6];break;
						case 0x7f:P2 = seg_key[7];break;
						default:break;
					}
			 }		 
		key_flag = 1 ;
		}
	}
}