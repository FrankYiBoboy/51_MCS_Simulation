#include <reg51.h>
sbit P20 = P2^0;
sbit P21 = P2^1;
void main()
{
while(1)
{
	P20 = 0;
	P21 = 1;
}
}