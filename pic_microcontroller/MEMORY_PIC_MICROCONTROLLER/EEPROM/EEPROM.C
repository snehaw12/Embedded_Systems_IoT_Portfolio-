#include<p18f4520.h>
void EEPROM_write(unsigned char ,unsigned char);
void main()
{
EEPROM_write(0x40,'B');
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


	