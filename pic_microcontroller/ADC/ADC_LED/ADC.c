#include<p18f4520.h>
void ADC_init();
void ADC_read();
void main()
{TRISB=0x00;
ADC_init();
while(1)
{
ADC_read();
}
}
void ADC_read()
{ADCON0bits.GO=1;
while(ADCON0bits.GO==1);
PORTB=ADRESL;
}
void ADC_init()
{
ADCON0=0x11;
ADCON1=0x00;
ADCON2=0xA5;
}