#ifndef BLINKING_LED_H
#define BLINKING_LED_H

#include <Arduino.h>

#include "void_loop.h"

class BlinkingLED: public ScheduledLoop {
public:
  bool enabled = true;
  void setup(uint8_t pin);

protected:
  void runScheduled();

private:
  uint8_t pin;
  bool state = false;
};

#endif
