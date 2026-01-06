/*************************************************************
  Blynk is a platform with iOS and Android apps to control
  ESP32, Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build mobile and web interfaces for any
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: https://www.blynk.io
    Sketch generator:           https://examples.blynk.cc
    Blynk community:            https://community.blynk.cc
    Follow us:                  https://www.fb.com/blynkapp
                                https://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on ESP32 chip.

  NOTE: This requires ESP32 support package:
    https://github.com/espressif/arduino-esp32

  Please be sure to select the right ESP32 module
  in the Tools -> Board menu!

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <ESP32Servo.h>

/* Fill in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID           "TMPL3khan02P9"
#define BLYNK_TEMPLATE_NAME         "Led Operation"
#define BLYNK_AUTH_TOKEN            "J8QSB52QWE1Ry7sAfQpP4OB1TzPf0Vak"

int servoPin = 13;

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Teknomindz_Airtel";
char pass[] = "India@2024";


Servo myservo;  // create servo object to control a servo
// 16 servo objects can be created on the ESP32

BLYNK_WRITE(V1)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  // You can also use:
  // String i = param.asStr();
  // double d = param.asDouble();
  Serial.print("V1 Slider value is: ");
  Serial.println(pinValue);
  myservo.write(pinValue);
}
void setup()
{
  // Debug console
  Serial.begin(9600);
  myservo.attach(servoPin); // attaches the servo on pin 13 to the servo object
  pinMode(2,INPUT);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop()
{
  Blynk.run();
  int x=digitalRead(2);
  if(x==HIGH)
  {
    Blynk.virtualWrite(V0,"Led on");
    
  }
  else
  {
    Blynk.virtualWrite(V0,"Led off");
  }
}

