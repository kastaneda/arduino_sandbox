#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

byte ua_coat_of_arms[8] = {
  B10001,
  B10101,
  B10101,
  B10101,
  B11011,
  B11111,
  B00100,
  B00000,
};

byte char_l[8] = {
  B00000,
  B00000,
  B00111,
  B01001,
  B10001,
  B10001,
  B10001,
  B00000,
};

byte char_v[8] = {
  B00000,
  B00000,
  B11110,
  B10001,
  B11110,
  B10001,
  B11110,
  B00000,
};

byte char_Y[8] = {
  B10001,
  B10001,
  B10001,
  B01111,
  B00001,
  B10001,
  B01110,
  B00000,
};

byte char_k[8] = {
  B00000,
  B00000,
  B10001,
  B10010,
  B11100,
  B10010,
  B10001,
  B00000,
};

byte char_yi[8] = {
  B01010,
  B00000,
  B01100,
  B00100,
  B00100,
  B00100,
  B01110,
  B00000,
};

byte char_n[8] = {
  B00000,
  B00000,
  B10001,
  B10001,
  B11111,
  B10001,
  B10001,
  B00000,
};

byte char_test[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
};

void setup() {
  lcd.createChar(0, ua_coat_of_arms);
  lcd.createChar(1, char_l);
  lcd.createChar(2, char_v);
  lcd.createChar(3, char_Y);
  lcd.createChar(4, char_k);
  lcd.createChar(5, char_yi);
  lcd.createChar(6, char_n);
  lcd.createChar(7, char_n);

  lcd.begin(16, 2);  

  lcd.print("C\1a\2a \3\4pa\5\6i! ");
  lcd.write(byte(0));
}

void loop() {}
