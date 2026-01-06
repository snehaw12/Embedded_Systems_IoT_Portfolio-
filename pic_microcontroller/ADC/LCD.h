#include<P18F4520.h>
#define LCD PORTD
#define RS PORTCbits.RC1
#define RW PORTCbits.RC0
#define E PORTCbits.RC2
void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void lcd_str(unsigned char*);
void delay(int);
void LCD_init(void);
void lcd_cmd(unsigned char x)
{
	LCD = x; // pass data on dataline
	RS = 0;  // Configure RS in command mode
	RW = 0;	// Configure RW in write mode
	E = 1; // Enable high 
	delay(4);
	E = 0; // Enable low , to generate the pulse of some delay 
}
void lcd_data(unsigned char x)
{
	LCD = x; // pass data on dataline
	RS = 1;  // Configure RS in data mode interpret as a data
	RW = 0;	// Configure RW in write mode
	E = 1; // Enable high 
	delay(4);
	E = 0; // Enable low , to generate the pulse of some delay 
}

void lcd_str(unsigned char *p)
{
  while(*p!='0')
 {
	lcd_data(*p);
	p++;
 }
}

void delay(int t)
{
	int i,j;
	for(i=0;i<t;i++)
		for(j=0;j<100;j++);
}
void LCD_init(void)
{
 TRISC = 0x00;
 TRISD = 0x00;
 lcd_cmd (0x38);
 lcd_cmd (0x01);
 lcd_cmd (0x0C);
 lcd_cmd (0x80);
 
}
