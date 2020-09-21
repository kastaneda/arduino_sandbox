#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
byte screen[2][16];

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

  for (byte i = 0; i < 2; i++)
    for (byte j = 0; j < 16; j++)
      screen[i][j] = 32;
}


void loop() {
  byte i;

  if (Serial.available()) {
    // wait for data in the buffer
    delay(100);

    // scroll screen
    for (i = 0; i < 16; i++) {
      screen[0][i] = screen[1][i];
      screen[1][i] = 32;
    }

    i = 0;
    while (Serial.available() > 0) {
      int c = Serial.read();

      if (c == 10)
        i = 16;

      if (i < 16)
        screen[1][i++] = c;
    }

    lcd.clear();
    for (i = 0; i < 2; i++) {
      lcd.setCursor(0, i);
      for (byte j = 0; j < 16; j++)
        lcd.write(screen[i][j]);
    }

    beep();
  }
}
