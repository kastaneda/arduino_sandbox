/* Servo knob + debounced attach/detach
 * Based on Debounce and Knob examples
 */

#include <Servo.h>

Servo myServo;

const int potPin = A0;
const int servoPin = 9;
const int buttonPin = 2;
const int ledPin = 13;

int ledState = HIGH;
int buttonState;
int lastButtonState = LOW;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);
  myServo.attach(servoPin);
}

void loopDebounce() {
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) {
        ledState = !ledState;
        digitalWrite(ledPin, ledState);
        if (ledState) {
          myServo.attach(servoPin);
        } else {
          myServo.detach();
        }
      }
    }
  }

  lastButtonState = reading;
}

void loopKnob()
{
  int potReading = analogRead(potPin);
  int servoVal = map(potReading, 0, 1023, 0, 180);
  myServo.write(servoVal);
}  

void loop() {
  loopKnob();
  loopDebounce();
}