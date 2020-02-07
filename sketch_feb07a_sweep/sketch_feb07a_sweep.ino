#include <Servo.h>

Servo myservo;

int pos = 0;

int startPos = 30;
int endPos = 150;

void setup() {
  myservo.attach(9);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  for (pos = startPos; pos <= endPos; pos += 1) {
    myservo.write(pos);
    delay(15);
  }
  delay(500);

  digitalWrite(LED_BUILTIN, LOW);
  for (pos = endPos; pos >= startPos; pos -= 1) {
    myservo.write(pos);
    delay(15);
  }
  delay(500);
}
