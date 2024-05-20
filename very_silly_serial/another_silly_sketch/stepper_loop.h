#ifndef STEPPER_LOOP_H
#define STEPPER_LOOP_H

#include <Arduino.h>

#include "void_loop.h"

class StepperLoop: public ScheduledLoop {
public:
  void setTargetStep(long target);
  long getCurrentStep();
  bool isBusy();
  void setup(uint8_t pin0, uint8_t pin1, uint8_t pin2, uint8_t pin3);

  static const byte stepSequence[];

protected:
  void runScheduled();

private:
  uint8_t pin[4];
  long currentStep;
  long targetStep;
  void setMotorState(byte bitMaskState);
};

#endif
