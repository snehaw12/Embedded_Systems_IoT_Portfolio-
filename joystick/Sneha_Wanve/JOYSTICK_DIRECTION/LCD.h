#include<p18f4520.h>
void lcd_init(void);
void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void lcd_string(unsigned char *);
void delay(int);
void lcd_init(void)
#define LCD PORTD
#define RS  PORTCbits.RC1
#define RW  PORTCbits.RC0
#define E   PORTCbits.RC2
{
TRISC=0x00;
TRISD=0x00;
lcd_cmd(0x38);
lcd_cmd(0x01);
lcd_cmd(0x80);
lcd_cmd(0x0c);
}
void lcd_cmd(unsigned char c)
{
PORTD=c;
RS=1;
RW=0;
E=1;
delay(4);
E=0;
}

void lcd_data(unsigned char c)
{
PORTD=c;
RS=1;
RW=0;
E=1;
delay(4);
E=0;
}
void lcd_string(unsigned char *s)
{
	while(*s!='\0')
	{
	lcd_data(*s);
	s++;
	}
}
void delay(int t)
{
int i,j;
for(i=0;i<t;i++)
for(j=0;j<498;j++);
}
