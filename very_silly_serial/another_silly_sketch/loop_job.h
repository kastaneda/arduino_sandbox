#ifndef LOOP_JOB_H
#define LOOP_JOB_H

#include <Arduino.h>

class ShouldSetup {
public:
  virtual void setup() = 0;
};

class ShouldLoop {
public:
  virtual void loopAt(unsigned long timeNow) = 0;
  void loop();
};

class ScheduledLoop: public ShouldLoop {
public:
  unsigned long runPeriod = 1000000; // default: 1s
  void loopAt(unsigned long timeNow);

protected:
  virtual void runScheduled() = 0;
  unsigned long lastRun = 0;
};

#endif
