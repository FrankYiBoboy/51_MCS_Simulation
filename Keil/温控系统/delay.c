#include <delay.h>

void delay_us(unsigned char t)
{
	while(--t);
}

void delay_ms(unsigned char t)
{
	unsigned char i,j;  
	for(i=t;i>0;i--)
	{
		for(j=120;j>0;j--);
	}
}