#include "Arduino.h" 
#include "SillyStepper.h" 

SillyStepper::SillyStepper(byte pin0, byte pin1, byte pin2, byte pin3) {
  this->pin[0] = pin0;
  this->pin[1] = pin1;
  this->pin[2] = pin2;
  this->pin[3] = pin3;
  this->currentStep = 0;
  this->targetStep = 0;
  this->delayDurationMicros = 5000; // 5 ms per step
  this->lastRunMicros = micros();
}

void SillyStepper::setTargetStep(long step) {
  this->targetStep = step;
}

long SillyStepper::getCurrentStep() {
  return this->currentStep;
}

bool SillyStepper::isBusy() {
  return (this->currentStep != this->targetStep);
}

void SillyStepper::setMotorState(byte bitMaskState) {
  for (byte i = 0, j = 1; i < sizeof(this->pin); i++, j <<= 1) {
    digitalWrite(this->pin[i], (bitMaskState & j) ? HIGH : LOW);
  }
}

void SillyStepper::setup() {
  for (byte i = 0; i < sizeof(this->pin); i++) {
    pinMode(this->pin[i], OUTPUT);
    digitalWrite(this->pin[i], LOW);
  }
}

void SillyStepper::loopScheduled() {
  byte stepInSequence;
  if (this->isBusy()) {
    if (this->currentStep < this->targetStep) {
      this->currentStep++;
    } else {
      this->currentStep--;
    }
    stepInSequence = this->currentStep & B0011;
    this->setMotorState(SillyStepper::stepSequence[stepInSequence]);
  } else {
    this->setMotorState(0);
  }
}

// Full-step sequence
const byte SillyStepper::stepSequence[4] = {
  B1000,
  B0100,
  B0010,
  B0001
}; 
