#include<p18f4520.h>
#include "LCD.h"
void ADC_init(void);
int ADC_Read(void);


void main()
{ int x,i,a[4];
  ADC_init();
  lcd_init();
  while(1)
{ADCON0=0x11;
x=ADC_Read();
for(i=0;i<4;i++)
{	a[i]=x%10;
	x=x/10;
}
lcd_cmd(0x80);
for(i=3;i>=0;i--)
{
lcd_data(a[i]+'0');
}
ADCON0=0x19;
}
ADCON0=0x11;
x=ADC_Read();
for(i=0;i<4;i++)
{	a[i]=x%10;
	x=x/10;
}
lcd_cmd(0xC0);
for(i=3;i>=0;i--)
{
lcd_data(a[i]+'0');
}
ADCON0=0x19;
}
void ADC_init(void){

}
int ADC_Read(void){

}