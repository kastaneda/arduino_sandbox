#include "Arduino.h" 
#include "ScheduledJob.h" 

void ScheduledJob::loopWhen(unsigned long timeNowMicros) {
  unsigned long timeSinceLastRun;
  timeSinceLastRun = timeNowMicros - this->lastRunMicros;
  
  if (timeSinceLastRun >= this->delayDurationMicros) {
    this->loopScheduled();
    this->lastRunMicros = timeNowMicros;
  }
}

void ScheduledJob::setDelayDuration(unsigned long durationMicros) {
  if (this->delayDurationMicros == durationMicros) {
    return;
  }

  this->delayDurationMicros = durationMicros;
  this->lastRunMicros = micros();
}
