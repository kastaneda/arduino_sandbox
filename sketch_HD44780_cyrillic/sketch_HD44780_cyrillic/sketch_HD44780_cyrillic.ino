#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void beep() {
  digitalWrite(A0, LOW);
  delay(100);
  digitalWrite(A0, HIGH);
}

void setup() {
  lcd.begin(16, 2);
  lcd.print("hello, world!");

  pinMode(A0, OUTPUT);
  digitalWrite(A0, HIGH);

  beep();
}

void loop() {
}
