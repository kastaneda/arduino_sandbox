#ifndef BLINKING_LED_H
#define BLINKING_LED_H

#include <Arduino.h>

#include "loop_job.h"

class BlinkingLED: public ShouldSetup, public ScheduledLoop {
public:
  bool enabled = true;

  BlinkingLED(uint8_t pin);
  void setup();

protected:
  void runScheduled();

private:
  uint8_t pin;
  bool state = false;
};

#endif
