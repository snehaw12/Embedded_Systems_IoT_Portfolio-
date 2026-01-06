#include<lpc214x.h>
void LCD_CMD(unsigned char);
void LCD_DATA(unsigned char);
void delay(void);
int main()
{
	PINSEL0=0x00000000;	//gpio pin
	IO0DIR =0x00FF0E00;
	LCD_CMD(0x38);				// initializing 2 line in 8 bit mode
	
	
	