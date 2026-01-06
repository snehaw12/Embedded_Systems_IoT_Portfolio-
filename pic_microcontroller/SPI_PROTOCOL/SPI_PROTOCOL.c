#include<p18f4520.h>
void SPI_INIT(void);
void SPI_TR1(unsigned int);
void SPI_TR(unsigned int,unsigned int);
void DELAY_MS(int);

#define CS PORTAbits.RA5
int DATA1[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x64};
int ADR[8]={0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};

void main()
{
	int i,a,b,c,d,e,f,g,h;
	a=b=c=d=e=f=g=h=0;
	SPI_INIT();
	while(1)
	{
		SPI_TR(ADR[7],DATA1[a]);
		SPI_TR(ADR[6],DATA1[b]);
		SPI_TR(ADR[5],DATA1[c]);
		SPI_TR(ADR[4],DATA1[d]);
		SPI_TR(ADR[3],DATA1[e]);
		SPI_TR(ADR[2],DATA1[f]);
		SPI_TR(ADR[1],DATA1[g]);
		SPI_TR(ADR[0],DATA1[h]);
		a++;
		if(a==10)
		{
			a=0;
			b++;
		}
			if(b==0)
		{
			a=b=0;
			c++;
		}
			if(c==10)
		{
			a=b=c=0;
			d++;
		}
			if(d==10)
		{
			a=b=c=d=0;
			e++;
		}
			if(e==10)
		{
			a=b=c=d=e=0;
			f++;
		}
			if(f==10)
		{
			a=b=c=d=f=0;
			g++;
		}
			if(g==10)
		{
			a=b=c=d=e=f=g=0;
			h++;
		}
			if(g==10)
		{
			a=b=c=d=e=f=g=h=0;
		}
		
		DELAY_MS(490);
	}
}
void DELAY_MS(int val)
{
	int i,j;
	for (i=0;i<val;i++)
	for (j=0;j<498;j++);
}

void SPI_INIT(void)
{	
	TRISAbits.RA5=0;
	TRISCbits.RC3=0;
	TRISCbits.RC5=0;
	SSPSTAT=0xC0;
	SSPCON1=0x20;
	SPI_TR(0x0B,0x07);		//all 8 ssd's in use (scan limit)
	SPI_TR(0x09,0x00);		// decode off  due to binary (bcd) input
	SPI_TR(0x0A,0X0F);		//max intensity
	SPI_TR(0x0C,0x01);		//shutdown off
	SPI_TR(0x0F,0x00);		//display test off
}

void SPI_TR1(unsigned int X)
{
	SSPBUF=X;
	while(!PIR1bits.SSPIF);
		PIR1bits.SSPIF=0;
}
void SPI_TR(unsigned int cmd,unsigned int data)
{
	CS=0;
	SPI_TR1(cmd);
	SPI_TR1(data);
	CS=1;
	
}
	

	