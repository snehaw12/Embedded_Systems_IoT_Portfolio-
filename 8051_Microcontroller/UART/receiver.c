#include <reg51.h>
//serial UART
// receiver
void delay(int);
void trans (unsigned char);
unsigned char receive(void);
void main()
{ unsigned char r;
	TMOD = 0x20;		//timer 1 in 8 bit auto reload mode
	TH1 = 0xFD;		//band rate 9600
	SCON = 0x50;		//7 bit +start +Stop mode
	TR1 = 1;
	while(1)
	{
		r=receive();
		trans(r);
	}
}
void trans (unsigned char x)
{
	SBUF = x;
	while(TI==0);
	TI = 0;
}
unsigned char receive(void)
{
	unsigned char x;
	while(RI==0);
	RI = 0;
	x = SBUF;
	return x;
}

