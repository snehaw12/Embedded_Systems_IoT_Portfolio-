# OTP-Based Security System

## 📋 Project Overview

This project implements an **OTP (One-Time Password) Based Security System** with **RFID Card Authentication** using **PIC18F4520 microcontroller**. The system provides dual-layer security by first authenticating users with RFID cards, then verifying a 4-digit numerical password (OTP) via a 3x3 keypad matrix. Upon successful verification, an LED is activated granting access.

### Key Features
✅ **Dual-Layer Security** - RFID Card + 4-Digit Password verification
✅ **RFID Authentication** - 12-character unique card ID validation
✅ **Keypad Interface** - 3x3 matrix keypad for password input
✅ **Real-time LCD Display** - Shows system status and prompts
✅ **LED Access Control** - Visual indicator for granted/denied access
✅ **UART Communication** - 9600 baud rate serial interface
✅ **Enhanced Security** - Character-by-character verification

---

## 🛠️ Hardware Components

| Component | Specification | Purpose |
|-----------|---------------|---------|
| **Microcontroller** | PIC18F4520 | Main processor |
| **RFID Module** | Serial RFID Reader | Reads 12-character card ID |
| **LCD Display** | 16x2 Character LCD | Real-time status display |
| **Keypad** | 3x3 Matrix Keypad | Password input (1-9) |
| **LED** | 5V Red LED | Access granted indicator |
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
  RC2 → EN (Enable)
  RD0-RD7 → D0-D7 (Data lines)

Keypad Matrix (3x3):
  RB5 → Row 0 (R0)
  RB6 → Row 1 (R1)
  RB7 → Row 2 (R2)
  RB1 → Column 0 (C0)
  RB2 → Column 1 (C1)
  RB3 → Column 2 (C2)
  RB4 → Column 3 (C3)

LED Control:
  RB0 → LED (Access Granted)
```

### Keypad Matrix Layout

```
    C0  C1  C2  C3
R0  1   2   3   *
R1  4   5   6   #
R2  7   8   9   0

Used Keys: 1-9 (Numeric only)
Password: 4 digits (e.g., "2143")
```

---

## 💻 Code Structure & Explanation

### **Main Program Flow**

#### 1. **System Initialization**
```c
void main()
{
    // GPIO Configuration
    TRISB = 0x1E;           // RB1-RB4 (columns) as inputs, RB0,RB5-RB7 as outputs
    INTCON2bits.RBPU = 0;   // Enable internal pull-ups
    ADCON1 = 0x0F;          // Configure all pins as digital
    
    // Module Initialization
    led = 0;                // LED OFF initially
    lcd_init();             // Initialize LCD
    UART_init();            // Initialize UART at 9600 baud
    
    // Display Startup Message
    lcd_cmd(0x80);
    lcd_string("Scan RFID");
}
```

#### 2. **RFID Card Reading**
```c
// Array to store received RFID data (12 characters)
unsigned char g[12], x;

// Read 12 characters from RFID module via UART
for(i = 0; i < 12; i++)
{
    x = receive();    // Receive one character
    trans(x);         // Echo back
    g[i] = x;         // Store in array
}

// Verify if scanned card matches authorized card
if((g[0]=='0')&&(g[1]=='9')&&(g[2]=='0')&&(g[3]=='0')&&
   (g[4]=='1')&&(g[5]=='5')&&(g[6]=='F')&&(g[7]=='F')&&
   (g[8]=='E')&&(g[9]=='E')&&(g[10]=='0')&&(g[11]=='D'))
{
    // RFID Match - Proceed to password entry
    lcd_cmd(0x01);
    lcd_string("Enter Passward");
    lcd_cmd(0xC0);  // Move to second line
}
else
{
    // RFID Mismatch - Display error
    lcd_cmd(0x01);
    lcd_string("Wrong RFID");
    lcd_cmd(0xC0);
    lcd_string("Scan Again");
}
```

#### 3. **Keypad Scanning (3x3 Matrix)**
```c
unsigned char s[4];  // Store 4-digit password
int i = 0;

while(i < 4)
{
    // Row 0 Scan
    r0 = 0;  // Pull Row 0 LOW
    r1 = r2 = 1;  // Keep Row 1,2 HIGH
    
    if(c0 == 0) { lcd_data('1'); s[i] = '1'; i++; delay(200); }
    if(c1 == 0) { lcd_data('2'); s[i] = '2'; i++; delay(200); }
    if(c2 == 0) { lcd_data('3'); s[i] = '3'; i++; delay(200); }
    
    // Row 1 Scan
    r1 = 0;  // Pull Row 1 LOW
    r0 = r2 = 1;  // Keep Row 0,2 HIGH
    
    if(c0 == 0) { lcd_data('4'); s[i] = '4'; i++; delay(200); }
    if(c1 == 0) { lcd_data('5'); s[i] = '5'; i++; delay(200); }
    if(c2 == 0) { lcd_data('6'); s[i] = '6'; i++; delay(200); }
    
    // Row 2 Scan
    r2 = 0;  // Pull Row 2 LOW
    r0 = r1 = 1;  // Keep Row 0,1 HIGH
    
    if(c0 == 0) { lcd_data('7'); s[i] = '7'; i++; delay(200); }
    if(c1 == 0) { lcd_data('8'); s[i] = '8'; i++; delay(200); }
    if(c2 == 0) { lcd_data('9'); s[i] = '9'; i++; delay(200); }
}
```

#### 4. **Password Verification**
```c
// Authorized password: "2143"
if((s[0] == '2') && (s[1] == '1') && 
   (s[2] == '4') && (s[3] == '3'))
{
    // Password Match
    lcd_cmd(0x01);
    lcd_string("Access granted");
    led = 0xFF;  // Turn ON LED
}
else
{
    // Password Mismatch
    lcd_cmd(0x01);
    lcd_string("Access denyed");
    led = 0x00;  // Keep LED OFF
}
```

---

## 🔧 Function Descriptions

### **LCD Functions**

#### Initialize LCD
```c
void lcd_init(void)
{
    TRISC = 0x00;   // Control pins as output
    TRISD = 0x00;   // Data pins as output
    lcd_cmd(0x30);  // Wake up sequence
    lcd_cmd(0x38);  // 8-bit mode, 2 lines, 5×8 font
    lcd_cmd(0x01);  // Clear display
    lcd_cmd(0x80);  // Set cursor to first line
    lcd_cmd(0x0C);  // Display ON, cursor OFF, blink OFF
}
```

#### Send Command (Instruction)
```c
void lcd_cmd(unsigned char x)
{
    LCD = x;        // Put command on D0-D7
    RS = 0;         // Register Select = 0 (Instruction mode)
    RW = 0;         // Read/Write = 0 (Write)
    EN = 1;         // Enable pulse
    delay(10);
    EN = 0;
}
```

#### Send Data (Character)
```c
void lcd_data(unsigned char x)
{
    LCD = x;        // Put character on D0-D7
    RS = 1;         // Register Select = 1 (Data mode)
    RW = 0;         // Read/Write = 0 (Write)
    EN = 1;         // Enable pulse
    delay(10);
    EN = 0;
}
```

#### Display String
```c
void lcd_string(unsigned char *p)
{
    while(*p != '\0')  // Until null terminator
    {
        lcd_data(*p);  // Display each character
        p++;
    }
}
```

### **UART Functions**

#### Initialize UART
```c
void UART_init(void)
{
    TRISC = 0x80;    // RC7=input(RX), RC6=output(TX)
    TXSTA = 0x24;    // TXEN=1(enable TX), BRGH=1(high baud rate)
    RCSTA = 0x90;    // SPEN=1(enable serial port), CREN=1(enable RX)
    SPBRG = 0x81;    // Baud rate = 9600 @ 20MHz
}
```

#### Receive Data via UART
```c
unsigned char receive(void)
{
    while(PIR1bits.RCIF == 0);  // Wait for data
    return RCREG;                // Return received character
}
```

#### Transmit Data via UART
```c
void trans(unsigned char x)
{
    TXREG = x;                      // Load into transmit register
    while(TXSTAbits.TRMT == 0);     // Wait for transmission
}
```

### **Delay Function**
```c
void delay(int t)
{
    int i, j;
    for(i = 0; i < t; i++)
        for(j = 0; j < 500; j++);  // 500 cycles per loop
    // Total delay ≈ t × 500 / Clock_Speed
}
```

---

## 📊 System Flow Diagram

```
┌──────────────────────────────────────┐
│   System Initialization               │
│  - Configure Ports (TRIS)             │
│  - Initialize LCD                     │
│  - Initialize UART (9600)             │
│  - Enable Internal Pull-ups           │
└─────────────┬────────────────────────┘
              │
              ▼
┌──────────────────────────────────────┐
│   Display "Scan RFID"                 │
│   Wait for RFID card                  │
└─────────────┬────────────────────────┘
              │
              ▼
┌──────────────────────────────────────┐
│   Receive 12 characters via UART      │
│   from RFID module                    │
└─────────────┬────────────────────────┘
              │
         ┌────┴────┐
         │          │
         ▼          ▼
     Match      Mismatch
    RFID ID     RFID ID
         │          │
         ▼          │
  ┌──────────────┐  │
  │Display:      │  │
  │"Enter        │  │
  │Passward"     │  │
  │              │  │
  │Scan Keypad   │  │
  │(4 digits)    │  │
  └───┬──────────┘  │
      │             │
      ▼             ▼
 ┌─────────┐   ┌─────────────┐
 │Password │   │"Wrong RFID" │
 │Match    │   │"Scan Again" │
 │"2143"   │   │             │
 └────┬────┘   └─────┬───────┘
      │              │
 ┌────┴──────┐       │
 │            │       │
 ▼            ▼       ▼
 Access   Access  Return to
 Granted  Denied  Start
 LED ON   LED OFF
```

---

## 🔐 Security Features Implemented

| Feature | Description | Benefit |
|---------|-------------|---------|
| **RFID Authentication** | 12-character card ID verification | Prevents unauthorized card usage |
| **Dual-Layer Security** | Password required after card match | Adds second security layer |
| **Character Verification** | Character-by-character comparison | Prevents partial/altered access |
| **Keypad Matrix** | Reliable mechanical input method | Prevents false triggers |
| **Visual Feedback** | LCD status display | User knows system state |
| **LED Indicator** | Physical access confirmation | Clear visual grant/deny status |
| **Debounce Delay** | 200ms delay between key presses | Eliminates contact bounce errors |
| **Timeout Mechanism** | Auto-reset after verification | Prevents unauthorized loitering |

---

## 🚀 How to Use

### **Step 1: Hardware Setup**
1. Connect PIC18F4520 to programmer/debugger
2. Interface RFID reader to UART pins (RC6, RC7)
3. Connect 16x2 LCD to Port C (control) and Port D (data)
4. Connect 3x3 keypad matrix to Port B
5. Connect LED to RB0 for access indication
6. Apply 5V power supply

### **Step 2: Customize Credentials**

**Authorized RFID ID:**
```c
// Line 55 in OTP_Based_Security_Systeam.c
// Replace with your card ID
if((g[0]=='0')&&(g[1]=='9')&&(g[2]=='0')&&(g[3]=='0')&&
   (g[4]=='1')&&(g[5]=='5')&&(g[6]=='F')&&(g[7]=='F')&&
   (g[8]=='E')&&(g[9]=='E')&&(g[10]=='0')&&(g[11]=='D'))
```

**Authorized Password:**
```c
// Line 145 in OTP_Based_Security_Systeam.c
// Replace with your 4-digit password
if((s[0]=='2')&&(s[1]=='1')&&(s[2]=='4')&&(s[3]=='3'))
```

### **Step 3: Compile & Program**
1. Open MPLAB X IDE
2. Load project file (.mcp)
3. Compile using XC8 compiler
4. Program hex file into PIC18F4520

### **Step 4: Operation**
1. Power on the system
2. LCD displays "Scan RFID"
3. Scan authorized RFID card
4. If match → LCD displays "Enter Passward"
5. Enter 4-digit password using keypad
6. If correct → "Access granted" + LED ON
7. If incorrect → "Access denyed" + LED OFF
8. System auto-resets for next user

---

## 📝 Default Credentials

| Item | Value | Notes |
|------|-------|-------|
| **RFID Card ID** | 090015FFEE0D | 12-character hex code |
| **Password** | 2143 | 4-digit numerical |
| **UART Baud Rate** | 9600 | @ 20MHz clock |
| **Keypad Debounce** | 200ms | Prevents bounce errors |

---

## 🐛 Troubleshooting

| Issue | Cause | Solution |
|-------|-------|----------|
| LCD not displaying | Port configuration error | Check TRISC/TRISD settings |
| RFID card not reading | UART baud rate mismatch | Verify SPBRG = 0x81 |
| Keypad not responding | Pull-up not enabled | Set INTCON2bits.RBPU = 0 |
| LED not turning ON | Port B config issue | Verify TRISB = 0x1E |
| Wrong character displayed | Character encoding | Check LCD data mode (RS=1) |
| Erratic behavior | Clock frequency | Use 20 MHz crystal oscillator |
| RFID always shows "Wrong" | Incorrect card ID | Verify and update g[] array |

---

## 📚 Alternative Implementations

### **RFID_OTP_Code.c (ESP32 Version)**
This implementation integrates with ESP32 for:
- Dynamic OTP generation
- Remote server verification
- Wireless communication support
- Cloud-based credential management

### **Key Differences:**
- OTP is generated externally (ESP32)
- Supports 6-digit OTP instead of 4-digit password
- UART communication with external OTP generator
- Display asterisks (*) for masked password entry

---

## 📚 References

- **PIC18F4520 Datasheet** - Microchip Technologies
- **RFID Reader Serial Protocol** - Device documentation
- **16x2 LCD HD44780** - Controller datasheet
- **3x3 Keypad Matrix** - Standard multiplexing technique

---

## 📝 Author

**Sneha Wanve**  
Embedded Systems & IoT Portfolio

---

## 📄 License

This project is part of the Embedded Systems & IoT Portfolio and is available for educational purposes.

---

## 🎯 Future Enhancements

- [ ] Multi-user database with EEPROM storage
- [ ] Timestamp logging with RTC integration
- [ ] SMS alerts using GSM module
- [ ] Cloud integration via WiFi/Bluetooth
- [ ] Biometric authentication (fingerprint/face)
- [ ] Dynamic OTP generation with time-based validation
- [ ] Attendance tracking system
- [ ] Mobile app integration for credential management
- [ ] Emergency override mechanisms
- [ ] Audit trail with SD card storage

---

## 🔧 Project Files

```
OTP_Based_Security_Systeam/
├── OTP_based_security_systeam/
│   ├── OTP_Based_Security_Systeam.c    (Main implementation)
│   ├── RFID_OTP_Code.c                 (Alternative ESP32 version)
│   ├── LCD.h                            (LCD driver header)
│   ├── *.hex                            (Compiled hex files)
│   ├── *.cof                            (Debug files)
│   └── esp32_rfid/                      (ESP32 integration)
├── try_and_error/                       (Development versions)
└── Double security with RFID and Passw.txt (Project notes)
```

---

## 📧 Support & Feedback

For questions or improvements, refer to the portfolio repository or contact the author.
