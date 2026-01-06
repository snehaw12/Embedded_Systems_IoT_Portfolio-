//Double security with RFID and Passward. 
//LCD display scan RFID, if RFID is correct then show Enter passward, else show Wrong RFID scan again, if enterd passward is correct then display access granted and led turn on, else display access denyed.

#include<p18f4520.h>
#define LCD PORTD

#define RS PORTCbits.RC1
#define RW PORTCbits.RC0
#define EN PORTCbits.RC2

#define r0 PORTBbits.RB5
#define r1 PORTBbits.RB6
#define r2 PORTBbits.RB7
#define c0 PORTBbits.RB1
#define c1 PORTBbits.RB2
#define c2 PORTBbits.RB3
#define c3 PORTBbits.RB4
#define led PORTBbits.RB0

void lcd_init (void);
void lcd_data (unsigned char);
void lcd_cmd (unsigned char);
void delay (int);

void lcd_string(unsigned char *)
;
void UART_init(void);
void trans(unsigned char);
unsigned char receive (void);

void main()
{
unsigned char a[16]="Scan RFID",b[16]="Enter Passward",c[16]="Access granted",d[16]="Access denyed",e[16]="Wrong RFID",f[16]="Scan Again";
unsigned char g[12],x,s[4];

int i;
led=0; 
lcd_init();
UART_init();
TRISB= 0x1E;
INTCON2bits.RBPU = 0;
ADCON1 = 0x0F;

lcd_cmd(0x80);
lcd_string(a);

while(1)
{
for(i=0;i<12;i++)
{
x=receive();
trans(x);
g[i]=x;
}
if((g[0]=='0')&&(g[1]=='9')&&(g[2]=='0')&&(g[3]=='0')&&(g[4]=='1')&&(g[5]=='5')&&(g[6]=='F')&&(g[7]=='F')&&(g[8]=='E')&&(g[9]=='E')&&(g[10]=='0')&&(g[11]=='D'))
{
lcd_cmd(0x01);
lcd_cmd(0x80);
lcd_string(b);
lcd_cmd(0xC0);

i=0;
while(i<4)
{
r0=0;
r1=r2=1;
if(c0==0)
{
lcd_data('1');
s[i]='1';
i++;
delay(200);
}

if(c1==0)
{
lcd_data('2');
s[i]='2';
i++;
delay(200);
}

if(c2==0)
{
lcd_data('3');
s[i]='3';
i++;
delay(200);
}

r1=0;
r0=r2=1;
if(c0==0)
{
lcd_data('4');
s[i]='4';
i++;
delay(200);
}

if(c1==0)
{
lcd_data('5');
s[i]='5';
i++;
delay(200);
}

if(c2==0)
{
lcd_data('6');
s[i]='6';
i++;
delay(200);
}

r2=0;
r0=r1=1;
if(c0==0)
{
lcd_data('7');
s[i]='7';
i++;
delay(200);
}

if(c1==0)
{
lcd_data('8');
s[i]='8';
i++;
delay(200);
}

if(c2==0)
{
lcd_data('9');
s[i]='9';
i++;
delay(200);
}

}

if((s[0]=='2')&&(s[1]=='1')&&(s[2]=='4')&&(s[3]=='3'))
{
lcd_cmd(0x01);
lcd_cmd(0x80);
lcd_string(c);
led = 0xFF;
}
else
{
lcd_cmd(0x01);
lcd_cmd(0x80);
lcd_string(d);
}
}
else
{
lcd_cmd(0x01);
lcd_cmd(0x80);
lcd_string(e);
lcd_cmd(0xC0);
lcd_string(f);
}
}
}

void UART_init(void)
{
TRISC = 0x80;
TXSTA = 0x24;
RCSTA = 0x90;
SPBRG = 0x81;
}

void trans (unsigned char x)
{
TXREG = x;
while(TXSTAbits.TRMT == 0);
}

unsigned char receive(void)
{
while(PIR1bits.RCIF == 0);
return RCREG;
}

void lcd_init(void)
{
TRISC = 0x00;
TRISD = 0x00;
lcd_cmd(0x30);
lcd_cmd(0x38);
lcd_cmd(0x01);
lcd_cmd(0x80);
lcd_cmd(0x0C);
}

void lcd_cmd(unsigned char x)
{
LCD = x;
RS = 0;
RW = 0;
EN = 1;
delay(10);
EN = 0;
}

void lcd_data(unsigned char x)
{
LCD = x;
RS = 1;
RW = 0;
EN = 1;
delay(10);
EN = 0;
}

void delay (int t)
{
int i,j;
for(i=0;i<t;i++)
for(j=0;j<500;j++);
}

void lcd_string (unsigned char *p)
{
while(*p!='\0')
{
lcd_data(*p);
p++;
}
}