#ifndef BLINKING_LED_H
#define BLINKING_LED_H

#include <Arduino.h>

#include "loop_job.h"

class BlinkingLED: public ShouldSetup, public ScheduledLoop {
public:
  bool enabled = true;

  BlinkingLED(byte pin);
  void setup();

protected:
  void runScheduled();

private:
  byte pin;
  bool state = false;
};

#endif
