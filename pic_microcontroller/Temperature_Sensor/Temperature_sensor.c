#include<p18f4520.h>
#include"LCD.h"
void ADC_init(void);
int ADC_read(void);   
void main()
{int d,res1,res2,alt;
float temp,an;
ADC_init();
LCD_init();
lcd_data('A');
while(1)
{
d=ADC_read();
an=0.00488*d;
temp=an*100;
res1=temp;
lcd_cmd(0x80);
lcd_data((res1/10)+'0');
lcd_data((res1%10)+'0');
lcd_data('.');
res2=(temp-res1)*100;
lcd_data((res2/10)+'0');
lcd_data((res2%10)+'0');
lcd_data(223);
lcd_data('C');
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
ADCON0=0x19;
ADCON1=0x00;
ADCON2=0xA5;
}
