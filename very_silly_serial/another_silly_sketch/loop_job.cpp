#include "loop_job.h"

void ShouldLoop::loop() {
  this->loopAt(micros());
}

void ScheduledLoop::loopAt(unsigned long timeNow) {
  if ((timeNow - this->lastRun) >= this->runPeriod) {
    this->runScheduled();
    this->lastRun = timeNow;
  }
}
