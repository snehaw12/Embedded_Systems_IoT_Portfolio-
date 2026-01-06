#include<LPC214x.h>
int main()
{
	IO0DIR |= (1<<6);
	IO0DIR &= ~((1<<5)&(1<<7));;
	IO0CLR |= (1<<6);
	while(1)
	{
		if((IO0PIN & (1<<5)) == 0)
		{
			IO0SET |=(1<<6);
    }
		if((IO0PIN & (1<<7)) == 0)
		{
			IO0CLR |=(1<<6);
    }
  }
}

