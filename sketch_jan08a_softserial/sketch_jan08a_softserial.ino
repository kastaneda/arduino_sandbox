#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

void setup()  
{
  Serial.begin(57600);
  Serial.write("* * * Hello UART\n");

  // DAMN IT DOES NOT SEND "OK" RESPONSE TO MY "AT"!

  mySerial.begin(9600);
  //delay(250);
  //mySerial.write("AT+NAMEArduinoBluetooth\n\r");
  // OKsetname
}

void loop()
{
  if (mySerial.available()) {
    delay(50);
    Serial.write("\n* * * Responce: ");
    while(mySerial.available()) {
      byte c = mySerial.read();
      Serial.write(c);
    }
    Serial.write("\n");
  }

  if (Serial.available()) {
    delay(50); // wait a little
    Serial.write("\n* * * Got input: ");
    while(Serial.available()) {
      byte c = Serial.read();
      Serial.write(c);
      mySerial.write(c);
    }
    Serial.write("\n");
    mySerial.write("\n\r");
  }
}
