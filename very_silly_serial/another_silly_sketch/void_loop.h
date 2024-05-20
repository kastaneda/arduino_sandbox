#ifndef VOID_LOOP_H
#define VOID_LOOP_H

#include <Arduino.h>

class VoidLoop {
public:
  virtual void loopAt(unsigned long timeNow) = 0;
  void loop();
};

class ScheduledLoop: public VoidLoop {
public:
  unsigned long runPeriod = 1000000; // default: 1s
  void loopAt(unsigned long timeNow);

protected:
  virtual void runScheduled() = 0;
  unsigned long lastRun = 0;
};

#endif
