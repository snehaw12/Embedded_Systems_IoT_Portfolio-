#include<lpc214x.h>
int main()
{
	int i;
	
	PINSEL1=0X00080000;
	while(1)
	{
		for(i=0;i<1024;i++)
		{
			DACR=(i<<6)|(1<<16);
		}
	}
}
