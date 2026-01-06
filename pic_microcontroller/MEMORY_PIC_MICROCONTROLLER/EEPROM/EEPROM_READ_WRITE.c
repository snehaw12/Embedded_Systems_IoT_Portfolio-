#include<p18f4520.h>
#include"LCD.h"
unsigned char EEPROM_Read(unsigned char);
void EEPROM_write(unsigned char ,unsigned char);

void main()
{
int t=0x40,i;
unsigned char x,array[10]="sneha";
LCD_INIT();
for(i=0;i<5;i++)
{
EEPROM_write(t,array[i]);
t++;
}
t=0x40;
for(i=0;i<5;i++)
{
x=EEPROM_Read(t);
LCD_DATA(x);
t++;
}
while(1);
}
void EEPROM_write(unsigned char adr,unsigned char data)
{ 
EECON1bits.EEPGD=0;	//data EEPROM selection
EEADR=adr;
EEDATA=data;
INTCONbits.GIE=0;	//disable inturrept
EECON1bits.WREN=1;		//write enable 
EECON2=0x55;
EECON2=0xAA;
EECON1bits.WR=1;	//start writing process
while(EECON1bits.WR==1);//wait until writing completes
EECON1bits.WREN=0;	//write disable
INTCONbits.GIE=1;	//enable interrupt
}
unsigned char EEPROM_Read(unsigned char adr)
{
EECON1bits.EEPGD=0;		//data memory EEPROM Selection
EEADR=adr;
EECON1bits.RD=1;		//start reading process
while(EECON1bits.RD==1);
return EEDATA ;      //return data read and store into EEDATA
}
