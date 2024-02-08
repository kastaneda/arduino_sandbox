#include "Arduino.h" 

void setup() {
  pinMode(2, INPUT_PULLUP);
  Serial.begin(9600);
}

byte lastState = 0;

void loop() {
  byte reading = digitalRead(2);
  if (reading != lastState) {
    Serial.println(reading);
  }
  lastState = reading;
}
