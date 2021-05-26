#include <LiquidCrystal.h>

const byte rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const byte sensorPin = A0;

void setup() {
  lcd.begin(16, 2);
}

void loop() {
  unsigned int sensorValue;

  // sensorValue = analogRead(sensorPin);

  sensorValue = 0;
  for (byte i = 0; i < 64; i++)
    sensorValue += analogRead(sensorPin);
  sensorValue >>= 6;
  
  lcd.setCursor(0, 0);
  lcd.print("A0 = ");
  if (sensorValue < 1000) lcd.print(" ");
  if (sensorValue < 100) lcd.print(" ");
  if (sensorValue < 10) lcd.print(" ");
  lcd.print(sensorValue);

  delay(250);
}
