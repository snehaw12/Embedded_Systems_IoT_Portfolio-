#include <p18f4550.h>
#include <string.h>

// Configuration bits settings
#pragma config FOSC = HS        // External crystal oscillator
#pragma config WDT = OFF        // Watchdog timer disabled
#pragma config LVP = OFF        // Low voltage programming disabled
#pragma config PBADEN = OFF     // PORTB<4:0> pins are configured as digital I/O

// Define pins for motor control
#define M1_PLUS PORTDbits.RD0  // Motor 1 positive
#define M1_NEG  PORTDbits.RD1  // Motor 1 negative
#define M2_PLUS PORTDbits.RD2  // Motor 2 positive
#define M2_NEG  PORTDbits.RD3  // Motor 2 negative
#define M3_PLUS PORTDbits.RD4  // Motor 3 positive
#define M3_NEG  PORTDbits.RD5  // Motor 3 negative
#define M4_PLUS PORTDbits.RD6  // Motor 4 positive
#define M4_NEG  PORTDbits.RD7  // Motor 4 negative

// Function prototypes
void initialize(void);
void UART_Init(void);
void UART_Send_String(const char *str);
void UART_Send_Char(char data);
char UART_Receive_Char(void);
void process_command(char *command);
void move_forward(void);
void move_backward(void);
void turn_right(void);
void turn_left(void);
void stop_motors(void);
void LCD_Init(void);
void LCD_Command(char cmd);
void LCD_Data(char data);
void LCD_String(const char *str);

void main(void) {
    char received_data[20];
    unsigned char i = 0;

    initialize();
    UART_Init();
    LCD_Init();

    LCD_String("Robot Ready");

    while(1) {
        if(PIR1bits.RCIF) {  // Check if data is received
            char rx_data = UART_Receive_Char();

            if(rx_data == '\n' || rx_data == '\r') {
                received_data[i] = '\0';
                process_command(received_data);
                i = 0;
            } else {
                received_data[i++] = rx_data;
                if(i >= 19) i = 0;  // Prevent buffer overflow
            }
        }
    }
}

void initialize(void) {
    // Configure all ports as digital
    ADCON1 = 0x0F;

    // Configure PORTD as output for motors
    TRISD = 0x00;
    PORTD = 0x00;  // All motors off initially

    // Configure PORTB for LCD
    TRISB = 0x00;

    // Enable global interrupts
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
}

void UART_Init(void) {
    // Configure UART for 9600 baud rate with 20MHz crystal
    TRISCbits.TRISC7 = 1;    // RX pin as input
    TRISCbits.TRISC6 = 0;    // TX pin as output

    SPBRG = 129;             // For 9600 baud rate
    TXSTA = 0x20;            // Transmit enabled, async mode
    RCSTA = 0x90;            // Serial port enabled, continuous receive

    PIE1bits.RCIE = 1;       // Enable UART receive interrupt
}

void process_command(char *command) {
    LCD_Command(0x01);  // Clear LCD
    LCD_String(command);

    if(strstr(command, "forward")) {
        move_forward();
    }
    else if(strstr(command, "backward")) {
        move_backward();
    }
    else if(strstr(command, "right")) {
        turn_right();
    }
    else if(strstr(command, "left")) {
        turn_left();
    }
    else if(strstr(command, "stop")) {
        stop_motors();
    }
}

void move_forward(void) {
    // Set motor pins according to truth table
    PORTD = 0b01010101;  // M1+,M2+,M3+,M4+ high; All negative pins low
}

void move_backward(void) {
    // Set motor pins according to truth table
    PORTD = 0b10101010;  // M1-,M2-,M3-,M4- high; All positive pins low
}

void turn_right(void) {
    // Set motor pins according to truth table for right turn
    PORTD = 0b01100110;
}

void turn_left(void) {
    // Set motor pins according to truth table for left turn
    PORTD = 0b10011001;
}

void stop_motors(void) {
    PORTD = 0x00;  // All motors off
}

// Basic LCD functions (assumes 4-bit mode)
void LCD_Init(void) {
    __delay_ms(20);
    LCD_Command(0x02);  // Return home
    LCD_Command(0x28);  // 4-bit mode, 2 lines
    LCD_Command(0x0C);  // Display ON, cursor OFF
    LCD_Command(0x06);  // Increment cursor
    LCD_Command(0x01);  // Clear display
}

void LCD_Command(char cmd) {
    PORTB = (PORTB & 0xF0) | (cmd >> 4);
    PORTB &= ~0x20;  // RS = 0 for command
    PORTB |= 0x40;   // EN = 1
    __delay_us(1);
    PORTB &= ~0x40;  // EN = 0
    __delay_us(100);

    PORTB = (PORTB & 0xF0) | (cmd & 0x0F);
    PORTB |= 0x40;   // EN = 1
    __delay_us(1);
    PORTB &= ~0x40;  // EN = 0
    __delay_ms(5);
}

void LCD_Data(char data) {
    PORTB = (PORTB & 0xF0) | (data >> 4);
    PORTB |= 0x20;   // RS = 1 for data
    PORTB |= 0x40;   // EN = 1
    __delay_us(1);
    PORTB &= ~0x40;  // EN = 0
    __delay_us(100);

    PORTB = (PORTB & 0xF0) | (data & 0x0F);
    PORTB |= 0x40;   // EN = 1
    __delay_us(1);
    PORTB &= ~0x40;  // EN = 0
    __delay_ms(5);
}

void LCD_String(const char *str) {
    while(*str) LCD_Data(*str++);
}
