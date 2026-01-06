#include<p18f4520.h>
#include"LCD.h"
unsigned char EEPROM_Read(unsigned char);

void main()
{
unsigned char x;
LCD_INIT();
x=EEPROM_Read(0x40);
LCD_DATA(x);
while(1);
}
unsigned char EEPROM_Read(unsigned char adr)
{
EECON1bits.EEPGD=0;		//data memory EEPROM Selection
EEADR=adr;
EECON1bits.RD=1;		//start reading process
while(EECON1bits.RD==1);
return EEDATA ;      //return data read and store into EEDATA
}
