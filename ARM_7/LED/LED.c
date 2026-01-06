#include<lpc214x.h>
void delay(void);
int main()
{
	PINSEL0=0x00000000;
	IO0DIR =0x00000003;
	while(1)
	{
		IO0SET=0x00000001;
		IO0CLR=0x00000002;
		delay();
		IO0CLR=0x00000001;
		IO0SET=0x00000002;
		delay();
	}
}

void delay(void)
{ int i,j;
	for (i=0;i<400;i++)
	for (j=0;j<400;j++);
}
