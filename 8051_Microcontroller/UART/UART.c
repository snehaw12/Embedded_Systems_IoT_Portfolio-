#include <reg51.h>
//serial UART
// transmission
void delay(int);
void trans (unsigned char);
void trans_string (char *);
void main()
{
	TMOD = 0x20;		//timer 1 in 8 bit auto reload mode
	TH1 = 0xFD;		//band rate 9600
	SCON = 0x40;		//7 bit +start +Stop mode
	TR1 =1;
	while(1)
	{
		trans_string("SNEHA");
		trans(13);
		trans_string("WANVE");
		trans(13);
		trans(13);
		delay(1000);
	}
}
void delay(int t)
{ int i,j;
	for (i=0;i<t;i++)
	for (j=0;j<100;j++);
}
void trans (unsigned char x)
{
	SBUF = x;
	while(TI==0);
	TI = 0;
}
void trans_string (char *p)
{
	while(*p!='\0')
	{
		trans(*p);
		p++;
	}
}
		
		
