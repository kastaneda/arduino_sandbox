#include <Arduino.h>

#define myLED 10

void setup() {
  pinMode(myLED, OUTPUT);
}

void loop() {
  digitalWrite(myLED, HIGH);
  delay(1000);
  digitalWrite(myLED, LOW);
  delay(1000);
}
