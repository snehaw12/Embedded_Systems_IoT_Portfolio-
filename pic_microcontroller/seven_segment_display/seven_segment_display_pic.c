#include<p18f4520.h>
char arr[10]={0xE7, 0x21, 0xCB, 0x6B, 0x2D, 0x6E,0xE6, 0x23, 0xFF, 0x7F};
char arr2[10]={0x08,0x04,0x02,0x01};
void delay (int);
void main()
{int i;
TRISD=0x00;
TRISA=0x00;
while(1)
{       
for(i=0;i<4;i++)
{
PORTA=arr2[3-i];
PORTD=arr[i+1];
delay(4);
}
}
}
void delay (int t)
{int i,j;
for (i=0;i<t;i++);
for (j=0;j<498;j++);
}