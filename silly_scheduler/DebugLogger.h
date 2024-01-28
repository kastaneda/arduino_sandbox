#ifndef DebugLogger_h
#define DebugLogger_h
#include "Arduino.h" 
#include "ScheduledJob.h" 

class DebugLogger: public ScheduledJob {
public:
  DebugLogger(int FIXME);
  void setValue(long value);
  void setup();
  void loopScheduled();

private:
  long debugValue;
};

#endif
