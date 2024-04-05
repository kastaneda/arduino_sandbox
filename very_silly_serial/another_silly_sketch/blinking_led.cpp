#include "blinking_led.h"

void BlinkingLED::setup(uint8_t pin) {
  this->pin = pin;
  pinMode(this->pin, OUTPUT);
  digitalWrite(this->pin, LOW);
}

void BlinkingLED::runScheduled() {
  this->state = this->enabled && !this->state;
  digitalWrite(this->pin, this->state ? HIGH : LOW);
}
