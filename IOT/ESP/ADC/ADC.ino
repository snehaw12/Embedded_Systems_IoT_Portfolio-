void setup() {
  // put your setup code here, to run once:
 Serial.begin(115200);
}
void loop() {
  // put your main code here, to run repeatedly:
 int x = analogRead(13);
 Serial.println(x);
 delay(1000);
}
