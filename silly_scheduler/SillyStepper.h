#ifndef SillyStepper_h
#define SillyStepper_h
#include "Arduino.h" 
#include "ScheduledJob.h" 

class SillyStepper: public ScheduledJob {
public:
  SillyStepper(byte pin0, byte pin1, byte pin2, byte pin3);
  void setTargetStep(long target);
  long getCurrentStep();
  bool isBusy();
  void setup();
  void loopScheduled();

  static const byte stepSequence[];

private:
  byte pin[4];
  long currentStep;
  long targetStep;
  void setMotorState(byte bitMaskState);
};

#endif
