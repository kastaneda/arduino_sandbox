#ifndef BEEPER_H
#define BEEPER_H

#include <Arduino.h>

#include "loop_job.h"

class Beeper: public ShouldSetup, public ShouldLoop {
public:
  bool enabled = true;

  Beeper(uint8_t pin);
  void setup();
  void loopAt(unsigned long timeNow);
  void beep();
  void beep(unsigned long duration);

protected:
  void runScheduled();

private:
  uint8_t pin;
  bool active = false;
  unsigned long beepStart;
  unsigned long beepDuration;
};

#endif
