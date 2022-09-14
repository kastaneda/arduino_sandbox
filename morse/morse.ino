#define debug 1

char* alphabet[] = {
  ".-",     // A
  "-...",   // B
  "-.-.",   // C
  "-..",    // D
  ".",      // E
  "..-.",   // F
  "--.",    // G
  "....",   // H
  "..",     // I
  ".---",   // J
  "-.-",    // K
  ".-..",   // L
  "--",     // M
  "-.",     // N
  "---",    // O
  ".--.",   // P
  "--.-",   // Q
  ".-.",    // R
  "...",    // S
  "-",      // T
  "..-",    // U
  "...-",   // V
  ".--",    // W
  "-..-",   // X
  "-.--",   // Y
  "--.."    // Z
};

char* numbers[] = {
  "-----",  // 0
  ".----",  // 1
  "..---",  // 2
  "...--",  // 3
  "....-",  // 4
  ".....",  // 5
  "-....",  // 6
  "--...",  // 7
  "---..",  // 8
  "----."   // 9
};

const unsigned int delayDit = 50;
const unsigned int delayDah = 3 * delayDit;
const unsigned int delayAfterBeep = delayDit;
const unsigned int delayAfterChar = 3 * delayDit - delayAfterBeep;
const unsigned int delayAfterWord = 7 * delayDit - delayAfterBeep - delayAfterChar;

const int beepPin = LED_BUILTIN;

void playDitDah(char code) {
  digitalWrite(beepPin, HIGH);
  if (code == '.') {
    delay(delayDit);
#ifdef debug
    Serial.print(".");
#endif
  } else {
    delay(delayDah);
#ifdef debug
    Serial.print("-");
#endif
  }
  digitalWrite(beepPin, LOW);
  delay(delayAfterBeep);
}

void playDitDahSequience(char* sequence) {
  byte i = 0;
  while (sequence[i]) {
    playDitDah(sequence[i++]);
  }
  delay(delayAfterChar);
}

void playChar(char c) {
  if (c >= 'A' && c <= 'Z') {
    playDitDahSequience(alphabet[c - 'A']);
  }
  if (c >= 'a' && c <= 'z') {
    playDitDahSequience(alphabet[c - 'a']);
  }
  if (c >= '0' && c <= '9') {
    playDitDahSequience(numbers[c - '0']);
  }
  if (c == ' ') {
    delay(delayAfterWord);
  }
}

void playString(char* str) {
  unsigned int i = 0;
  while (str[i]) {
#ifdef debug
    Serial.print(str[i]);
    Serial.print("   ");
#endif
    playChar(str[i++]);
#ifdef debug
    Serial.println();
#endif
  }
}

void setup() {
  for (byte i = 2; i <= 13; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  for (byte i = A0; i <= A5; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
#ifdef debug
  Serial.begin(9600);
#endif
  delay(1000);
  playString("The quick brown fox jumps over the lazy dog");
}

void loop() {
}
