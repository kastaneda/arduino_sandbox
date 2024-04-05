#include "my_servo.h"

void MyServo::setup(uint8_t pin) {
  this->pin = pin;
  pinMode(this->pin, OUTPUT);
  digitalWrite(this->pin, LOW);
  this->runPeriod = 500000; // 0.5 s should be enough?
}

void MyServo::write(int angle) {
  if (angle != this->angle) {
    this->angle = angle;
    if (!this->attached) {
      this->attached = true;
      this->servo.attach(this->pin);
    }
    this->servo.write(angle);
    this->lastRun = micros();
  }
}

void MyServo::runScheduled() {
  if (this->attached) {
    this->servo.detach();
    this->attached = false;
  }
}
