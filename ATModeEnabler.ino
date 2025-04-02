#include <SoftwareSerial.h>
 
SoftwareSerial BTSerial(10, 11); // TX | RX
 
void setup()
{
  Serial.begin(9600);
  Serial.println("Waiting : ");
  BTSerial.begin(38400);  
}
 
void loop()
{
   if (BTSerial.available())
    Serial.write(BTSerial.read());
 
  if (Serial.available())
    BTSerial.write(Serial.read());
}