#include<reg51.h>
sbit LED1 = P1^2;
sbit LED2 = P1^3;
void delay (void);
void LED_ISRO(void) interrupt 0
{
  LED1 = 0;
	LED2 = 1;
	delay();
}
void main()
{ EA = 1;  //Enable
	EX0 = 1;  //enable into
	IT0 = 0;  //level trigger
	LED1 = 0;
	LED2 = 0;
	while(1)
	{
		LED1=1;
		LED2=0;
	}
}
void delay(void)
{ int i,j;
	for (i=0;i<300;i++)
	for (j=0;j<300;j++);
}