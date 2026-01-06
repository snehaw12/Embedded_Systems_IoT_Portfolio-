#include <reg51.h>
#define lcd P3
sbit r0 = P2^0;
sbit r1 = P2^1;
sbit r2 = P2^2;
sbit r3 = P2^3;
sbit c0 = P2^4;
sbit c1 = P2^5;
sbit c2 = P2^6;
sbit c3 = P2^7;
sbit rs = P1^0;
sbit rw = P1^1;
sbit e  = P1^2;

void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void delay (int);
void main()
{
	lcd_cmd(0x38);    //initializing two lines in 8 bit mode   
	lcd_cmd(0x01);   // clear
	lcd_cmd(0x0c);  //display on;display off;
	lcd_cmd(0x80);  //line 1 ; position 1


	while(1)
	{ 
		r0 = 0;
		r1=r2=r3=1;

		if (c0 == 0)
		{
			lcd_data('0');
		}	
		
			r3=0;
		r0=r1=r2=1;
		if (c1 == 0)
		{
			lcd_data ('1');
		}

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
{ 
	lcd = x;
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
		





















/*
// program on lcd
#include <reg51.h>
#define lcd P2
sbit rs = P1^0;
sbit rw = P1^1;
sbit e  = P1^2;
void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void delay (int);
void main()
{
	lcd_cmd(0x38);    //initializing two lines in 8 bit mode   
	lcd_cmd(0x01);   // clear
	lcd_cmd(0x0c);  //display on;display off;
	lcd_cmd(0x80);  //line 1 ; position 1
	// 
	lcd_data('h');
	lcd_data('e');
	lcd_data('l');
	lcd_data('l');
	lcd_data('0');
	lcd_cmd(0xc0); 
	lcd_data('w');
	lcd_data('o');
	lcd_data('r');
	lcd_data('l');
	lcd_data('d');
	while (1);
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
*/
