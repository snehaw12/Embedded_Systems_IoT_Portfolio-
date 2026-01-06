#include <reg51.h>
sbit r0 = P2^0;
sbit r1 = P2^1;
sbit r2 = P2^2;
sbit r3 = P2^3;
sbit c0 = P2^4;
sbit c1 = P2^5;
sbit c2 = P2^6;
sbit c3 = P2^7;
sbit led = P1^1;

void main()
{
	led = 0;
	while(1)
	{
		r0 = 0;
		r1=r2=r3=1;
		if ( c0==0)    // 1 pressed
		{ led =1;  //led on
		}
		r3=0;
		r0=r1=r2=1;
		if(c1==0)   // 0 pressed
		{
			led = 0;  //led off
		}
	}
}
