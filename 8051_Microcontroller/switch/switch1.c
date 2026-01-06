#include <reg51.h>
sbit switch1 = P1^3;
sbit led =P1^2;
//sbit switch2 = P1^5;
//sbit led1 = P1^4;
int main()
{
	led = 0;
	//led1 = 0;
	while(1)
	{
		if(switch1 == 1)
		{
			led = 1;
		}
		else
		{
			led = 0;
		}
	/*	if(switch2 == 0)
		{
			led1 = 1;
		}
		else
		{
			led1 = 0;
		}*/
	}
}
