#include<p18f4520.h>
#include "LCD.h"

// Function prototypes
void UART_init(void);
void lcd_init(void);
unsigned char receive(void);
void trans(unsigned char);
char scan_keypad(void);

void main()
{   
    int i,j,x,c;
    unsigned char Match[15]="Access Granted";
    unsigned char Mismatch[15]="Access Denied";
    unsigned char scan[15]="Scan card:";
    unsigned char enterOTP[15]="Enter OTP:";
    unsigned char a[13]="090015FFEE0D";
    unsigned char b[13];
    unsigned char otp_input[7];
    
    TRISB=0x00;
    TRISE=0x00;
    PORTE=0X00;
    
    lcd_init();
    UART_init();

    while(1)
    {
        lcd_cmd(0x01);
        lcd_cmd(0x80);                //Lcd display
        lcd_string(scan);
        PORTE=0x00;                    //buzzer off
        
        // RFID Card Reading - Your original code
        for(i=0;i<12;i++)         //RFID Accessed 
        {   
            x=receive();      
            b[i]=x;
            trans(x);
            c=0;
        }
        
        for(i=0;i<12;i++)        
        {
            if(b[i]==a[i])
            {
                c++;
            }
        }
        
        // If RFID matches, proceed to OTP
        if(c==12)
        {
            lcd_cmd(0x80);
            lcd_string(Match);
            delay(2000);  // Show RFID success briefly
            
            // Wait for OTP generation and display prompt
            lcd_cmd(0x01);
            lcd_string(enterOTP);
            lcd_cmd(0xC0);  // Move to second line
            
            // Get 6-digit OTP input
            for(i = 0; i < 6; i++) 
            {
                x = receive();  // Get OTP digit from ESP32
                otp_input[i] = x;
                lcd_data('*');  // Show * for entered digit
                trans(x);       // Send back to ESP32
            }
            otp_input[6] = '\0';
            
            // Get verification result from ESP32
            x = receive();
            
            lcd_cmd(0x01);
            if(x == '1') 
            {
                lcd_string(Match);
                PORTE=0x00;     // No buzzer
            }
            else 
            {
                lcd_string(Mismatch);
                PORTE=0xFF;     // Activate buzzer
            }
            delay(6000);
        }
        else
        {
            lcd_cmd(0x80);
            lcd_string(Mismatch);
            PORTE=0xFF;
            delay(6000);                //5 sec delay
        }
    }
}

// Your original UART and helper functions
void trans(unsigned char x)
{   
    TXREG =x;
    while(TXSTAbits.TRMT==0);
    TXSTAbits.TRMT=0;
}

void UART_init(void)
{
    TRISC=0x80;        //configr RC6 & RC7 pins in o/p & i/p mode
    TXSTA=0x24;        //TXEN=1,BRGH=1
    RCSTA=0x90;        //SPEN=1
    SPBRG=0x81;        //baud rate = 9600
}

unsigned char receive(void)
{
    while(PIR1bits.RCIF==0);
    PIR1bits.RCIF=0;
    return RCREG;
}