#ifndef ScheduledJob_h
#define ScheduledJob_h
#include "Arduino.h" 
#include "PeriodicJob.h" 

class ScheduledJob: public PeriodicJob {
public:
  unsigned long lastRunMicros;
  unsigned long delayDurationMicros;
  void loopWhen(unsigned long timeNowMicros);
  void setDelayDuration(unsigned long durationMicros);

protected:
  virtual void loopScheduled() = 0;
};

#endif
