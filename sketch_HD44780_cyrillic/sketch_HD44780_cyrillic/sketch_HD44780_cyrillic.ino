#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
byte prevLine[16];
byte nextLine[16];

void beep() {
  digitalWrite(A0, LOW);
  delay(100);
  digitalWrite(A0, HIGH);
}

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);

  pinMode(A0, OUTPUT);
  digitalWrite(A0, HIGH);

  for (byte i = 0; i < 16; i++) {
    prevLine[i] = 32;
  }
}


void loop() {
  byte i;

  if (Serial.available()) {
    delay(100);

    for (i = 0; i < 16; i++) {
      prevLine[i] = nextLine[i];
      nextLine[i] = 32;
    }

    i = 0;
    while (Serial.available() > 0) {
      int c = Serial.read();
      if (c == 10) {
        i = 16;
      }
      if (i < 16) {
        nextLine[i++] = c;
      }
    }

    lcd.clear();
    for (i = 0; i < 16; i++) {
      lcd.write(prevLine[i]);
    }

    lcd.setCursor(0, 1);
    for (i = 0; i < 16; i++) {
      lcd.write(nextLine[i]);
    }
  }
}
