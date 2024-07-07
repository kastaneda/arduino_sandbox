
#define MY_LED_PIN 2

void setup() {
  pinMode(MY_LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(MY_LED_PIN, HIGH);
  delay(1000);
  digitalWrite(MY_LED_PIN, LOW);
  delay(1000);
}
