#include<reg51.h>
sbit Led=P1^2;  //p1.2 defined as led
sbit Led2=P1^3;
void delay(void);
void main ()
{
Led = 0;   //led off
	Led2=0;
	while (1)
	{
		Led = 1;  // led on
		Led2=0;
		delay();
		Led = 0;
		Led2=1;
		delay();
}
}
void delay(void)
{ int i,j;
	for (i=0;i<400;i++)
	for (j=0;j<400;j++);
}