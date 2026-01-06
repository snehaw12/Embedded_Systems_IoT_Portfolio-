#include<lpc214x.h>
void RTC_INIT(void);
void LCD_INIT(void);
void LCD_CMD(unsigned char);
void LCD_DATA(unsigned char);
void LCD_STRING(unsigned char*);
void DELAY(void);
int main()
{
	PINSEL0=0x00000000;	//gpio pin
	IO0DIR =0x07F82A00;//hex value of numbers 0.9 ,0.11,0.13,0.19,0.26
	LCD_CMD(0x38);	// initializing 2 line in 8 bit mode
	LCD_CMD(0x01);
	LCD_CMD(0x0C);
	LCD_CMD(0x80);
	//LCD_STRING("HELLO");
	LCD_STRING("RTC Interface");
	RTC_INIT();
	LCD_CMD(0xC0);
	LCD_STRING("00:00:00");
	while(1)
	{
		LCD_CMD(0xC0);
		LCD_DATA((HOUR/10)+'0');
		LCD_DATA((HOUR%10)+'0');
		LCD_DATA(':');
		LCD_DATA((MIN/10)+'0');
		LCD_DATA((MIN%10)+'0');
		LCD_DATA(':');

}
}
void LCD_CMD(unsigned char x)
{
	IO0CLR=0X07F80000;
	IO0SET|=(x<<19);
  IO0CLR|=(1<<9);
	IO0CLR|=(1<<11);
	IO0SET|=(1<<13);
	DELAY();
	IO0CLR|=(1<<13);
}
void LCD_DATA(unsigned char x)
{
	IO0CLR=0X07F80000;
	IO0SET|=(x<<19);
  IO0SET|=(1<<9);
	IO0CLR|=(1<<11);
	IO0SET|=(1<<13);
	DELAY();
	IO0CLR|=(1<<13);
}
void DELAY(void)
{	int i,t,j;
	for(i=0;i<t;i++)
	for(j=0;j<100;j++);
}

void RTC_INIT(void)
{
	ILR=0x01;
	CCR=0x13;
	CCR=0X11;
	CIIR=0X01;
	SEC=00;
	MIN=36;
	HOUR=14;
}
void LCD_STRING(unsigned char *p)
{
	while(*p!='\0')
	{LCD_DATA(*p);
		p++;
	}
}
9*