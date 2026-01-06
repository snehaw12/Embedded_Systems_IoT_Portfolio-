#include <SinricPro.h>

#include <SinricPro.h>

#include <SinricPro.h>

// This example code is in the Public Domain (or CC0 licensed, at your option.)
// By Evandro Copercini - 2018
//
// This example creates a bridge between Serial and Classical Bluetooth (SPP)
// and also demonstrate that SerialBT have the same functionalities of a normal Serial
// Note: Pairing is authenticated automatically by this device

#include "BluetoothSerial.h"

String device_name = "Sneha_Wanve";

// Check if Bluetooth is available
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)  
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// Check Serial Port Profile (UART 1)
#if !defined(CONFIG_BT_SPP_ENABLED)  
#error Serial Port Profile for Bluetooth is not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);  //baude rate serial communication we cant select baude rate device itself select it
  SerialBT.begin(device_name);  //Bluetooth device name
  pinMode(2, OUTPUT);
   //direction
  //SerialBT.deleteAllBondedDevices(); // Uncomment this to delete paired devices; Must be called after begin
  Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());
}

void loop() {
  String str;
  char x;
  
  if (SerialBT.available()) {
    while(x!='*'){
      x=SerialBT.read();
    }
    while(x != '!')
    {
      x=SerialBT.read();
      str += x;
    }
    if (str=="LED ON !"){
      digitalWrite(2,HIGH);
       SerialBT.print("LED ON");
    }
    if(str=="LED OFF !"){
      digitalWrite(2,LOW);
      SerialBT.print("LED OFF");
    }
   
  }

  delay(20);
}

