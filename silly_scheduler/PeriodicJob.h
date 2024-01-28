#ifndef PeriodicJob_h
#define PeriodicJob_h
#include "Arduino.h" 

class PeriodicJob {
public:
  virtual void setup() = 0;
  virtual void loopWhen(unsigned long timeNowMicros) = 0;
  void loop();
};

#endif
