#include<reg51.h>
sbit led = P1^0;
sbit led_1= P1^1;
void delay (void);
void main()
{
	int i=0,j=0;
	led = 0;
	led_1=0;
	while(1)
	{
		if(i==1){
			led=~led;
			i=0;
		}
		if(j==4){
			led_1=~led_1;
			j=0;
		}

		delay();
		i++;
		j++;
	}
}
void delay (void)
{int i;
	TMOD = 0x01;     		//timer 0 configured in 16 bit mode (56320)	
	for(i=0;i<100;i++)
	{
	TH0 = 0xdc;						// th & tL loaded with dc00 hex value
	TL0 = 0x00;						//start timer 
	TR0 = 1;
	while(TF0 == 0);      //wait until timer overflow
	TF0 = 0;								//reset flag (TFO)
	TR0 = 0;
	}		//stop timer
}

