//
// LED fade-in and fade-out without PWM
//

// Built-in LED
#define LED_pin 13

int i, j;

void setup() {
  pinMode(LED_pin, OUTPUT);
}

void loop() {
  // Fade-in
  for(i = 10; i < 990; i += 3) {
    digitalWrite(LED_pin, HIGH);
    delayMicroseconds(i);
    digitalWrite(LED_pin, LOW);
    delayMicroseconds(1000 - i);
  }

  // Light
  digitalWrite(LED_pin, HIGH);
  delay(750);
  
  // Fade-out
  for(i = 990; i > 10; i -= 3) {
    digitalWrite(LED_pin, HIGH);
    delayMicroseconds(i);
    digitalWrite(LED_pin, LOW);
    delayMicroseconds(1000 - i);
  }
  
  // Dark
  digitalWrite(LED_pin, LOW);
  delay(750); 
}
