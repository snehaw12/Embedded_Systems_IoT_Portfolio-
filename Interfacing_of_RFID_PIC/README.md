[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

# RFID Interfacing with PIC Microcontroller

## 📋 Project Overview

This project implements an **RFID-based Access Control System** using a **PIC18F4520 microcontroller**. The system reads RFID card data via UART communication and compares it with a pre-stored ID. [...]

### Key Features
- ✅ RFID card reading and identification
- ✅ Real-time LCD display of access status
- ✅ Audible buzzer alert for unauthorized access
- ✅ UART serial communication at 9600 baud rate
- ✅ Secure access control with 12-character ID verification

---

## 🛠️ Hardware Components

| Component | Specification | Purpose |
|-----------|---------------|---------|
| **Microcontroller** | PIC18F4520 | Main processor |
| **RFID Module** | Serial RFID Reader | Reads RFID card data |
| **LCD Display** | 16x2 Character LCD | Displays access status |
| **Buzzer** | 5V Buzzer | Audible alert for denied access |
| **Crystal Oscillator** | 20 MHz | System clock |
| **Voltage Regulator** | 7805 | 5V power supply |

---

## 📍 Pin Configuration

### PIC18F4520 Pinout

```
UART Communication:
  RC6 (TX) → RFID Module RX
  RC7 (RX) → RFID Module TX

LCD Interface (8-bit Mode):
  RC0 → RW (Read/Write)
  RC1 → RS (Register Select)
  RC2 → E  (Enable)
  RD0-RD7 → D0-D7 (Data lines)

Buzzer Control:
  RE0-RE7 (PORTE) → Buzzer (Active High)

Port Configuration:
  TRISB = 0x00 (Output)
  TRISE = 0x00 (Output)
```

---

## 💻 Code Structure & Explanation

### **Main Program Flow**

#### 1. **Initialization**
```c
void main()
{
    TRISB = 0x00;   // Configure PORTB as output
    TRISE = 0x00;   // Configure PORTE as output
    PORTE = 0x00;   // Buzzer OFF initially
    
    LCD_INIT();     // Initialize 16x2 LCD
    UART_init();    // Initialize UART at 9600 baud
    LCD_DATA('A');  // Display startup character
}
```

#### 2. **RFID Scanning Loop**
```c
unsigned char a[13] = "090015FFEE0D";  // Authorized card ID
unsigned char b[13];                    // Scanned card ID

for(i = 0; i < 12; i++)  // Read 12 characters from RFID
{
    x = receive();   // Receive from UART
    b[i] = x;        // Store in array
    trans(x);        // Echo back (optional)
}
```

#### 3. **ID Verification**
```c
int c = 0;  // Match counter

for(i = 0; i < 12; i++)
{
    if(b[i] == a[i])  // Compare character by character
    {
        c++;
    }
}

if(c == 12)  // All 12 characters match
{
    LCD_string(Match);  // Display "Access Granted"
    PORTE = 0x00;       // Buzzer OFF
    delay(6000);        // 6000 cycles ≈ 6 seconds
}
else  // Mismatch detected
{
    LCD_string(Mismatch);  // Display "Access Denied"
    PORTE = 0xFF;          // Buzzer ON
    delay(6000);           // Alarm duration
}
```

---

## 🔧 Function Descriptions

### **UART Initialization**
```c
void UART_init(void)
{
    TRISC = 0x80;     // RC7=input(RX), RC6=output(TX)
    TXSTA = 0x24;     // TXEN=1(enable TX), BRGH=1(high baud rate)
    RCSTA = 0x90;     // SPEN=1(enable serial port), CREN=1(enable RX)
    SPBRG = 0x81;    // Baud rate = 9600 @ 20MHz clock
}
```

**Baud Rate Calculation:**
```
Fosc = 20 MHz
Baud Rate = Fosc / (16 × (SPBRG + 1)) = 20M / (16 × 130) ≈ 9615 baud
```

### **Receive Function**
```c
unsigned char receive(void)
{
    while(PIR1bits.RCIF == 0);  // Wait until data received
    PIR1bits.RCIF = 0;          // Clear receive interrupt flag
    return RCREG;               // Return received character
}
```

### **Transmit Function**
```c
void trans(unsigned char x)
{
    TXREG = x;                  // Load data into transmit register
    while(TXSTAbits.TRMT == 0); // Wait until transmission complete
    TXSTAbits.TRMT = 0;         // Clear transmit flag
}
```

### **LCD Control Functions**

#### LCD Initialization
```c
void LCD_INIT(void)
{
    TRISC = 0x00;    // Control pins as output
    TRISD = 0x00;    // Data pins as output
    
    LCD_CMD(0x38);   // 8-bit mode, 2 lines, 5×8 font
    LCD_CMD(0x01);   // Clear display
    LCD_CMD(0x0C);   // Display ON, cursor OFF, blink OFF
    LCD_CMD(0x80);   // Set cursor to first line
}
```

#### Send Command to LCD
```c
void LCD_CMD(unsigned char x)
{
    LCD = x;         // Put data on D0-D7 (PORTD)
    RS = 0;          // Register Select = 0 (Command mode)
    RW = 0;          // Read/Write = 0 (Write)
    E = 1;           // Enable pulse
    delay(4);
    E = 0;
}
```

#### Send Data (Character) to LCD
```c
void LCD_DATA(unsigned char x)
{
    LCD = x;         // Put character on D0-D7
    RS = 1;          // Register Select = 1 (Data mode)
    RW = 0;          // Write mode
    E = 1;           // Enable pulse
    delay(4);
    E = 0;
}
```

#### Display String
```c
void LCD_string(unsigned char *p)
{
    while(*p != '\0')  // Until null terminator
    {
        LCD_DATA(*p);  // Display each character
        p++;
    }
}
```

### **Delay Function**
```c
void delay(int t)
{
    int i, j;
    for(i = 0; i < t; i++)        // Outer loop
        for(j = 0; j < 498; j++);  // Inner loop (498 cycles)
    // Approximate delay = t × (498 cycles) / Clock_Speed
}
```

---

## 📊 System Flow Diagram

```
┌─────────────────────────────────────────┐
│     PIC18F4520 Initialization            │
│  - Configure Ports (TRIS registers)      │
│  - Initialize LCD Module                 │
│  - Initialize UART (9600 baud)           │
└──────────────┬──────────────────────────┘
               │
               ▼
┌─────────────────────────────────────────┐
│   Display "Scan card:" on LCD            │
│   Wait for RFID card                     │
└──────────────┬──────────────────────────┘
               │
               ▼
┌─────────────────────────────────────────┐
│   Receive 12 characters via UART         │
│   from RFID module                       │
└──────────────┬──────────────────────────┘
               │
               ▼
┌─────────────────────────────────────────┐
│   Compare received ID (b[])              │
│   with authorized ID (a[])               │
│   Character by character                 │
└──────────────┬──────────────────────────┘
               │
         ┌──────┴──────┐
         │             │
         ▼             ▼
     Match      Mismatch
     (c==12)    (c<12)
         │             │
         ▼             ▼
   ┌─────────┐   ┌──────────┐
   │ Grant   │   │  Deny    │
   │ Access  │   │ Access   │
   │ Buzzer  │   │ Buzzer   │
   │ OFF     │   │ ON       │
   └────┬────┘   └────┬─────┘
        │             │
        └──────┬──────┘
               ▼
         ┌──────────────────┐
         │  6 Second Delay  │
         └────────┬─────────┘
                  │
                  ▼
            Return to Scan
```

---

## 🚀 How to Use

### **Step 1: Hardware Setup**
1. Connect PIC18F4520 to programmer/debugger
2. Interface RFID module to UART pins (RC6, RC7)
3. Connect 16x2 LCD to Port C and Port D
4. Connect buzzer to Port E
5. Apply 5V power supply

### **Step 2: Code Configuration**
1. Update authorized RFID ID in code:
   ```c
   unsigned char a[13] = "090015FFEE0D";  // Replace with your card ID
   ```

2. Compile using MPLAB X IDE with XC8 compiler
3. Program the hex file into PIC18F4520

### **Step 3: Operation**
1. Power on the system
2. LCD displays "Scan card:"
3. Bring authorized RFID card near reader
4. System validates and displays result
5. Buzzer activates if access is denied

---

## 📝 RFID Card ID Format

- **Length:** 12 characters
- **Format:** Hexadecimal ASCII (0-9, A-F)
- **Example:** `090015FFEE0D`

**To find your card ID:**
1. Scan the card with RFID reader
2. Note the 12-character code displayed
3. Update the `a[]` array with this ID

---

## 🔐 Security Features

✅ **Character-by-character verification** - Prevents partial matches
✅ **Audio feedback** - Alerts on unauthorized access
✅ **Visual feedback** - LCD displays access status
✅ **Timeout mechanism** - 6-second delay between scans
✅ **Unique ID matching** - Only authorized cards grant access

---

## 🐛 Troubleshooting

| Issue | Cause | Solution |
|-------|-------|---------|
| LCD not displaying | Port configuration error | Check TRISC and TRISD settings |
| RFID not reading | UART baud rate mismatch | Verify SPBRG = 0x81 for 9600 baud |
| Buzzer always ON | PORTE initialization | Set PORTE = 0x00 initially |
| Incorrect card verification | Wrong authorized ID | Update `a[]` array with correct card ID |
| Erratic behavior | Clock frequency issue | Use 20 MHz crystal oscillator |

---

## 📚 References

- **PIC18F4520 Datasheet** - Microchip Technologies
- **RFID Reader Serial Protocol** - Device-specific documentation
- **16x2 LCD Module** - HD44780 controller datasheet

---

## 📝 Author

**Sneha Wanve**  
Embedded Systems & IoT Portfolio

---

## 📄 License

This project is part of the Embedded Systems & IoT Portfolio and is available for educational purposes.

---

## 🎯 Future Enhancements

- [ ] Multi-card database support (EEPROM storage)
- [ ] Real-time clock integration (timestamp logging)
- [ ] Keypad for manual password entry
- [ ] OLED display for enhanced UI
- [ ] Wireless communication (WiFi/Bluetooth)
- [ ] Card blocking/revocation mechanism
- [ ] Audit trail with SD card storage
