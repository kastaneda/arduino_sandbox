/*

    /----------------------[1]---[2]---[3]
    |                       |     |     |
    |                       |     |     |
    |     /----------------[4]---[5]---[6]
    |     |                 |     |     |
    |     |                 |     |     |
    |     |     /----------[7]---[8]---[9]
    |     |     |           |     |     |
    |     |     |           |     |     |
    |     |     |     /----[*]---[0]---[#]
    |     |     |     |     |     |     |
    |     |     |     |     |     |     |
    |     |     |     |     |     |     |
    |     |     |     |     |     |     |
   R1    R2    R3    R4    C1    C2    C3

*/

byte rows[] = {12, 11, 10, 9};
byte cols[] = {7, 6, 5};

char keyChars[] = "123456789*0#";

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN , OUTPUT);

  for (byte i=0; i<sizeof(rows); i++) {
    pinMode(rows[i], INPUT);
  }

  for (byte i=0; i<sizeof(cols); i++) {
    pinMode(rows[i], INPUT);
  }
}

char scanKeyboard() {
  char keyFound = 0;

  for (byte i=0; i<sizeof(rows); i++) {
    pinMode(rows[i], OUTPUT);
    digitalWrite(rows[i], LOW);
    for (byte j=0; j<sizeof(cols); j++) {
      pinMode(cols[j], INPUT_PULLUP);
      // LOW when pressed
      if (digitalRead(cols[j]) == LOW) {
        keyFound = keyChars[i*sizeof(cols) + j];
      }
      pinMode(cols[j], INPUT);
    }
    pinMode(rows[i], INPUT);
  }

  return keyFound;
}

void loop() {
  char prevKey = 0;
  char key;

  key = scanKeyboard();
  if (key != prevKey) {
    if (key) {
      Serial.println(key);
    }
    prevKey = key;
  }

  digitalWrite(LED_BUILTIN, key ? HIGH : LOW);
}
