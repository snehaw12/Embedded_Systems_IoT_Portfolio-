#include<p18f4520.h>
#define LCD PORTD
#define RS PORTCbits.RC1
#define RW PORTCbits.RC0
#define E  PORTCbits.RC2

void LCD_CMD(unsigned char);
void LCD_DATA(unsigned char);
void delay (int);
void LCD_INIT(void);
void LCD_string(unsigned char *);


void LCD_INIT(void){
	TRISC=0x00;
	TRISD=0x00;
	LCD_CMD(0x38);
	LCD_CMD(0x01);
	LCD_CMD(0x0c);
	LCD_CMD(0x80);
}
void LCD_CMD(unsigned char x)
{
	LCD=x;
	RS =0;
	RW =0;
	E =1;
	delay(4);
	E=0;
}
void LCD_DATA(unsigned char x)
{
	LCD=x;
	RS=1;
	RW=0;
	E=1;
	delay(4);
	E=0;
}
void LCD_string(unsigned char *p)
{
  while(*p != '\0')
	{ LCD_DATA (*p);
		p++;
	}
}

		
void delay (int t)
{
	int i,j;
	for(i=0;i<t;i++)
	for(j=0;j<498;j++);
}
