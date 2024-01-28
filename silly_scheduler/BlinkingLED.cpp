#include "Arduino.h" 
#include "BlinkingLED.h" 

BlinkingLED::BlinkingLED(int pin) {
  this->ledPin = pin;
  this->ledState = false;
  this->blinkEnabled = true;
  this->delayDurationMicros = 500000;
  this->lastRunMicros = micros();
}

void BlinkingLED::setBlinkEnabled(bool enabled) {
  this->blinkEnabled = enabled;
}

void BlinkingLED::setup() {
  pinMode(this->ledPin, OUTPUT);
}

void BlinkingLED::loopScheduled() {
  this->ledState = ! this->ledState;
  digitalWrite(this->ledPin, (this->blinkEnabled && this->ledState) ? HIGH : LOW);
}
