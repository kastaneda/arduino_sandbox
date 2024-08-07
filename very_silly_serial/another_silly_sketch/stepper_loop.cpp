#include "stepper_loop.h"

void StepperLoop::setTargetStep(long step) {
  this->targetStep = step;
}

long StepperLoop::getCurrentStep() {
  return this->currentStep;
}

bool StepperLoop::isBusy() {
  return (this->currentStep != this->targetStep);
}

void StepperLoop::setMotorState(uint8_t bitMaskState) {
  for (uint8_t i = 0, j = 1; i < sizeof(this->pin); i++, j <<= 1) {
    digitalWrite(this->pin[i], (bitMaskState & j) ? HIGH : LOW);
  }
}

void StepperLoop::setup(uint8_t pin0, uint8_t pin1, uint8_t pin2, uint8_t pin3) {
  this->pin[0] = pin0;
  this->pin[1] = pin1;
  this->pin[2] = pin2;
  this->pin[3] = pin3;
  this->currentStep = 0;
  this->targetStep = 0;
  this->runPeriod = 7500; // 7.5 ms per step
  this->lastRun = micros();
  for (uint8_t i = 0; i < sizeof(this->pin); i++) {
    pinMode(this->pin[i], OUTPUT);
    digitalWrite(this->pin[i], LOW);
  }
}

void StepperLoop::runScheduled() {
  uint8_t stepInSequence;
  if (this->isBusy()) {
    if (this->currentStep < this->targetStep) {
      this->currentStep++;
    } else {
      this->currentStep--;
    }
    stepInSequence = this->currentStep & B0011;
    this->setMotorState(StepperLoop::stepSequence[stepInSequence]);
  } else {
    this->setMotorState(0);
  }
}

// Full-step sequence
const uint8_t StepperLoop::stepSequence[4] = {
  B1100,
  B0110,
  B0011,
  B1001
};
