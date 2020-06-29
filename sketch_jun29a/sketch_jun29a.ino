
// Ultrasonic sensor module HC-SR04
#define trigPin 9
#define echoPin 10

// Buzzer TMB1205
#define buzzerPin 13

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);
}

// Get sensor echo duration in microseconds
// distance_cm = duration_microseconds * 0.034 / 2;
unsigned long measureEchoDuration() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  return pulseIn(echoPin, HIGH);
}

// Short beep
void beep() {
  digitalWrite(buzzerPin, HIGH);
  delay(35);
  digitalWrite(buzzerPin, LOW);
}

// Desired delay between beeps (milliseconds), depending on sensor distance (microseconds)
unsigned long delayBetweenBeeps(unsigned long echoDuration) {
  // Something very dumb: echoDuration / 8
  return echoDuration >> 3;
}

void loop() {
  // TODO
  // unsigned long next_beep;

  delay(delayBetweenBeeps(measureEchoDuration()));
  beep();
}
