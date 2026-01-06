#include<p18f4520.h>
//void trans_str(unsigned char *p);  //string display
void UART_init(void);
void trans(unsigned char);
unsigned char receiver(void);
void delay(int t);
void main()
{	
	//unsigned char a[8]="hello ";  //string 
	//unsigned char str1[8]="World ";
	unsigned char x;
	UART_init();
	while(1)
	{
//	trans_str(a);
//	trans(13);
//	trans_str(str1);
//	trans(13);
//	trans(13);
	x=receiver(); //for reciever
	trans(x);
	
	//delay(1000);
	}
}
void UART_init(void)
{
	TRISC=0x80;		//configr RC6 & RC7 pins in o/p & i/p mode
	TXSTA=0x24;		//TXEN=1,BRGH=1
	RCSTA=0x90;		//SPEN=1
	SPBRG=0x81;		//baud ratt = 9600
}
void trans(unsigned char x)
{	TXREG =x;
	while(TXSTAbits.TRMT==0)
	TXSTAbits.TRMT=0;
}
unsigned char receiver(void )
{	while(PIR1bits.RCIF==0);
	PIR1bits.RCIF=0;
	return RCREG;
}
void delay (int t)
{
	int i,j;
	for(i=0;i<t;i++)
	for(j=0;j<499;j++);
}
void trans_str(unsigned char *p)
{
	while(*p!='\0')
	{
	 trans(*p);
	 p++;
	}
}