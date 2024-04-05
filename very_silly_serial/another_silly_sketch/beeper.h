#ifndef BEEPER_H
#define BEEPER_H

#include <Arduino.h>

#include "loop_job.h"

class Beeper: public ShouldLoop {
public:
  void setup(uint8_t pin);
  void loopAt(unsigned long timeNow);
  void beep();
  void beep(unsigned long duration);

private:
  uint8_t pin;
  bool active = false;
  unsigned long beepStart;
  unsigned long beepDuration;
};

#endif
