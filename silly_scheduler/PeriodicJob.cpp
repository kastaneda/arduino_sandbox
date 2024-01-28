#include "Arduino.h" 
#include "PeriodicJob.h" 

void PeriodicJob::loop() {
  this->loopWhen(micros());
}
