#include<P18f4520.h>
void main ()
{
	TRISB=0x00;
	PORTB=0x00;
	while(1)
{ 
	PORTB=0XB8;
} 