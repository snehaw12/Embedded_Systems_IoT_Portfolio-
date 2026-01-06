#include<p18f4520.h>
#define R0 PORTBbits.RB5
#define R1 PORTBbits.RB6
#define R2 PORTBbits.RB7
#define C0 PORTBbits.RB1
#define C1 PORTBbits.RB2
#define C2 PORTBbits.RB3
#define C3 PORTBbits.RB4
void delay (void);
void main()
{
TRISB=0x1E;
INTCON2bits.RBPU=0;
ADCON1=0x0F;
while(1)
{
R0=0;
R1=R2=1;
if(C0==0)
{
PORTBbits.RB0=1;
}
if(C1==0)
{
PORTBbits.RB0=0;
}
}
}