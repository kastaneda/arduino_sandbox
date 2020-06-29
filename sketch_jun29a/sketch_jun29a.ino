
// Ultrasonic sensor module HC-SR04
#define trigPin 9
#define echoPin 10

// Buzzer TMB1205
#define buzzerPin 13

// Echo >= 85 ms means distance more than 1.5 m
#define pulseInTimeout 85000

// Do not beep on big distance
#define silentWhenTooFar 700

unsigned long lastBeep = 0, nextBeep = 1000000;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);

  // Serial.begin(9600); // debug
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
  return echoDuration / 10;
}

void loop() {
  unsigned long betweenBeeps;

  // Measure constantly
  betweenBeeps = delayBetweenBeeps(measureEchoDuration());
  // Serial.println(betweenBeeps); // debug
  nextBeep = min(nextBeep, lastBeep + betweenBeeps);

  if (millis() > nextBeep) {
    // Beep, if it's  close enough
    if ((nextBeep - lastBeep) < silentWhenTooFar) {
      beep();
    }

    lastBeep = millis();
    nextBeep = lastBeep + 1000000;
  }
}
