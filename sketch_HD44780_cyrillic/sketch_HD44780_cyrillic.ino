#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
byte screen[2][16];

byte charUppercaseYi[8] = {
  B01010,
  B01110,
  B00100,
  B00100,
  B00100,
  B00100,
  B01110,
  B00000
};

byte charLowercaseYi[8] = {
  B01010,
  B00000,
  B01100,
  B00100,
  B00100,
  B00100,
  B01110,
  B00000
};

byte charUppercaseYe[8] = {
  B01110,
  B10001,
  B10000,
  B11110,
  B10000,
  B10001,
  B01110,
  B00000
};

byte charLowercaseYe[8] = {
  B00000,
  B00000,
  B01110,
  B10000,
  B11110,
  B10000,
  B01110,
  B00000
};

byte charUppercaseGhe[8] = {
  B00001,
  B11111,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B00000
};

byte charLowercaseGhe[8] = {
  B00000,
  B00001,
  B11111,
  B10000,
  B10000,
  B10000,
  B10000,
  B00000
};

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

  lcd.createChar(1, charUppercaseYi);
  lcd.createChar(2, charLowercaseYi);
  lcd.createChar(3, charUppercaseYe);
  lcd.createChar(4, charLowercaseYe);
  lcd.createChar(5, charUppercaseGhe);
  lcd.createChar(6, charLowercaseGhe);

  beep();
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
