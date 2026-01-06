#include<p18f4520.h>
#include"LCD.h"
void ADC_init(void);
int ADC_read(void);   
void main()
{int x,i,a[4];
TRISB=0x00;
ADC_init();
lcd_init();
lcd_data('0');
while(1)
{
x=ADC_read();

for(i=0;i<4;i++)
{
   a[i]=x%10;
x=x/10;
}
lcd_cmd(0xc0);
for(i=3;i>=0;i--)
{
lcd_data(a[i]+'0');
}
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
ADCON0=0x11;
ADCON1=0x00;
ADCON2=0xA5;
}
