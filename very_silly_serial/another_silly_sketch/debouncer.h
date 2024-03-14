#ifndef DEBOUNCER_H
#define DEBOUNCER_H

#include <Arduino.h>

#include "loop_job.h"

class Debouncer: public ShouldLoop {
public:
  int stateDebounced = 0;
  unsigned long debounceDelay = 50000; // 50ms

  int (*readingSource)() = 0;
  void (*onRaise)() = 0;
  void (*onFall)() = 0;
  void (*onChange)(int state) = 0;

  void loopAt(unsigned long timeNow);

private:
  int lastReading = 0;
  unsigned long lastDebounceTime = 0;
};

#endif

