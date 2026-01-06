#include<p18f4520.h>
#include "LCD.h"
void RTC_INIT(void);
void RTC_WRITE(void);
void READ_TIME(void);
void START(void);
void STOP (void);
void Check (void);
void I2C_DATA(unsigned char);
void I2C_READ(void);
void DISPLAY(void);

int arr[8];
char time[8];
int i,m;
int sec,min,hr;

//LCD Declaration

char time[8];

void main()
{
	unsigned char str[15]="RTC Interface";   //"RTC Interface";
	LCD_INIT();
	RTC_INIT();
	LCD_string(str);
	RTC_WRITE();
	LCD_CMD(0XC0);
	LCD_DATA('R');
	while(1){
	READ_TIME();
}
	
}

void RTC_INIT(void)
{
	TRISCbits.TRISC3=1;   //RC3-SCL-i/p
	TRISCbits.TRISC4=1;	//RC4-SDA-i/p
	SSPCON1=0x28;		//SSPEN=1,Master mode
	SSPSTAT=0x80;		//SPM=1(100khz mode) bit6 cke=0
	PIE1bits.SSPIE=1;   //Inturrept Unable.( inturrept generation)
	SSPADD=49;  		//100khz bit frequancy (frequancy in case of master mode)
}

void RTC_WRITE(void)
{
	START();
	I2C_DATA(0xD0);					//RTC slave add
	I2C_DATA(0x00);					//set word address to seconds register
	I2C_DATA(0x00);					//DATA(00sec)
	I2C_DATA(0x21);					//DATA/(20min)
	I2C_DATA(0x02);					//DATA(02hr)
	STOP();							// stop bit
}

void START(void)
{
	PIR1bits.SSPIF=0;				//clear flag
	SSPCON2bits.SEN=1;				//generate start bit
	while(PIR1bits.SSPIF==0);		//wait for start bit transmission
	PIR1bits.SSPIF=0;				//clear flag 
}

void STOP(void)
{
	PIR1bits.SSPIF=0;				//clear flag
	SSPCON2bits.PEN=1;				//generate stop bit
	while(PIR1bits.SSPIF==0);		//wait for stop bit transmission
	PIR1bits.SSPIF=0;				//clear flag 
}

void I2C_DATA(unsigned char c)
{
	SSPBUF=c;						//Load data into buffer
	while(PIR1bits.SSPIF==0);		//wait for acknowledgement  (data transmission) 
	PIR1bits.SSPIF=0;				//clear flag
}

void READ_TIME(void)					//continuos data transfering
{
	START();							//start
	I2C_DATA(0xD0);						//Data Write
	I2C_DATA(0x00);						//Data Read
	STOP();								//stop 

	I2C_READ();							//Reading Data
	DISPLAY();							//Display
}

void I2C_READ(void)
{
	START();
	I2C_DATA(0XD1);						//Slave Read Address
	
	for(i=0;i<2;i++)					
	{
		SSPCON2bits.RCEN=1;				//Receive Enable
	while(PIR1bits.SSPIF==0);			//Wait for data to receive
		PIR1bits.SSPIF=0;				//clear flag
		SSPCON2bits.ACKDT=0;			//Acknowledgment=0
		SSPCON2bits.ACKEN=1;			//send ACK
		while(PIR1bits.SSPIF==0);		//Ack Sent Successfully
		PIR1bits.SSPIF=0;
		m=SSPBUF;						//data saved to m
		arr[i]=m;						//M's Data in Array
		PIR1bits.SSPIF=0;				//Stoping Recieving data 
		SSPCON2bits.RCEN=0;				//disable data
	}

	SSPCON2bits.RCEN=1;					
	while(PIR1bits.SSPIF==0);
	PIR1bits.SSPIF=0;
	SSPCON2bits.ACKDT=1;				//Ack=1
	SSPCON2bits.ACKEN=1;
	while(PIR1bits.SSPIF==0);
	PIR1bits.SSPIF=0;
	m=SSPBUF;
	arr[i]=m;
	SSPCON2bits.RCEN=0;
	PIR1bits.SSPIF=0;
	STOP();
}

void Check(void)
{
	char x;
	while(PIR1bits.SSPIF==0);
	PIR1bits.SSPIF=0;
	x=SSPBUF;
}	

void DISPLAY(void)
{
	sec=arr[0];							//sec data
	min=arr[1];							//minute data
	hr=arr[2];							//hour data
	LCD_CMD(0xc0);						//Time display on second line

	time[0]=((hr & 0xF0)>>4)+'0';      //hour and hex value
	time[1]=(hr & 0x0F)+'0';		   //converted into character
	time[2]=':';
	time[3]=((min & 0xF0)>>4)+'0';	  //hour and hex value
	time[4]=(min & 0x0F)+'0';		  //converted into character
	time[5]=':';
	time[6]=((sec & 0xF0)>>4)+'0';	    //hour and hex value
	time[7]=(sec & 0x0F)+'0';	    	//converted into character
	
	for(i=0;i<8;i++)
	{
		LCD_DATA(time[i]);
	}
}

	
	
	
	
	
	
	