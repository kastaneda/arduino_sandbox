#ifndef DEBOUNCER_H
#define DEBOUNCER_H

#include <Arduino.h>

#include "loop_job.h"

class Debouncer: public ShouldLoop {
public:
  int stateDebounced = 0;
  unsigned long debounceDelay = 50000; // 50ms

  int (*readingSource)() = NULL;
  void (*onRaise)() = NULL;
  void (*onFall)() = NULL;
  void (*onChange)(int state) = NULL;

  void loopAt(unsigned long timeNow);

private:
  int lastReading = 0;
  unsigned long lastDebounceTime = 0;
};

#endif

