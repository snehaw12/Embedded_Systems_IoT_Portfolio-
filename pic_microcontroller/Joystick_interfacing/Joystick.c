#include<p18f4520.h>
#include"LCD.h"
void ADC_init(void);
int ADC_read(void);   
void main()
{int x,i,a[4];
 ADC_init();
 LCD_INIT();
while(1)
{
ADCON0=0x11;   //AN4 selected
x=ADC_read();
for(i=0;i<4;i++)
{
a[i]=x%10;
x=x/10;
}
LCD_CMD(0x80);   //set cursor to line 2 ,pos 1
for(i=3;i>=0;i--)
{
LCD_DATA(a[i]+'0');
}
ADCON0=0x19;
x=ADC_read();
for(i=0;i<4;i++)
{
a[i]=x%10;
x=x/10;
}
LCD_CMD(0xC0);   //set cursor to line 2 ,pos 1
for(i=3;i>=0;i--)
{
LCD_DATA(a[i]+'0');
}
ADCON0=0x19;
}
}
int ADC_read(void)
{int x;
 ADCON0bits.GO=1;
 while(ADCON0bits.GO==1);
 x=ADRESH;
 x=(x<<8);
 x|=ADRESL;
 return x;
}
void ADC_init(void)
{
 ADCON1=0x00;
 ADCON2=0xA5;
}
