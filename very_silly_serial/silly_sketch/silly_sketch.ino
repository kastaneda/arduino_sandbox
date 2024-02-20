void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}

#define updateDelay 500000
unsigned long lastUpdate_A0 = 0;

#define readBufSize 64
char readBuf[readBufSize];
unsigned int readBufCount = 0;

char myLedControl[] = "dev/board05/led/set";
// mosquitto_pub -h 192.168.0.82 -t dev/board05/led/set -m 1
// mosquitto_pub -h 192.168.0.82 -t dev/board05/led/set -m 0

void handleReadBuf() {
  unsigned int i;
  for(i = 0; myLedControl[i]; i++) {
    if (myLedControl[i] != readBuf[i]) return;
  }
  digitalWrite(LED_BUILTIN, (readBuf[i+1] == '1') ? HIGH : LOW);
}

void loop() {
  unsigned long timeNow = micros();

  if ((timeNow - lastUpdate_A0) >= updateDelay) {
    Serial.print("dev/board05/A0 ");
    Serial.println(analogRead(A0), DEC);
    lastUpdate_A0 = timeNow;
  }

  if (Serial.available() > 0) {
    char incomingChar = Serial.read();
    if (readBufCount < readBufSize) {
      readBuf[readBufCount++] = incomingChar;
    }
    if (incomingChar == '\n') {
      handleReadBuf();
      readBufCount = 0;
    }
  }
}
