// program on lcd
#include <reg51.h>
#define lcd P2
sbit rs = P1^0;
sbit rw = P1^1;
sbit e  = P1^2;
void lcd_str(unsigned char*);
void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void delay (int);
void main()
{
	lcd_cmd(0x38);    //initializing two lines in 8 bit mode   
	lcd_cmd(0x01);   // clear
	lcd_cmd(0x0c);  //display on;display off;
	lcd_cmd(0x80);  //line 1 ; position 1
	lcd_str("hello");
	while (1);
}
void lcd_str(unsigned char *p)
{
	while (*p != '\0')
	{ 
		lcd_data(*p);
		p++;
	}
}

void lcd_cmd(unsigned char x)
{
	lcd = x;  //pass data on dataline
	rs  = 0;  //configure rs in command mode
	rw = 0;   // configure rw in write mode
	e = 1;    // enable high
	delay(4);    
	e = 0;    //enable high
}
void lcd_data(unsigned char x)
{ lcd = x;
	rs = 1;
	rw = 0;
	e = 1;
	delay(4);
	e = 0;
}
void delay(int t)
{
	int i,j;
	for(i=0;i<t;i++)
	for(j=0;j<100;j++);
}
