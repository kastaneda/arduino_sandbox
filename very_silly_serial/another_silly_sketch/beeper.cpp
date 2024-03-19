#include "beeper.h"

Beeper::Beeper(uint8_t pin) {
  this->pin = pin;
}

void Beeper::setup() {
  pinMode(this->pin, OUTPUT);
  digitalWrite(this->pin, LOW);
}

void Beeper::beep() {
  this->beep(75000); // 75ms
}

void Beeper::beep(unsigned long duration) {
  digitalWrite(this->pin, HIGH);
  this->active = true;
  this->beepStart = micros();
  this->beepDuration = duration;
}

void Beeper::loopAt(unsigned long timeNow) {
  if (this->active) {
    if ((timeNow - this->beepStart) >= this->beepDuration) {
      digitalWrite(this->pin, LOW);
      this->active = true;
    }
  }
}
