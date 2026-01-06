#include<WiFi.h>
#define ssid " True Beauty "
#define Pass " @sneha70"

void Setup() {
Serial.begin (115208);
Serial.println ("connecting to wifi");
while (WiFi status() != WL_Connected)
{
Wifi.begin (ssid, Pass);

delay (5000);

Serial.Print ("-");

}

Serial.println (WiFi.localIp());

}

void.loop()

}