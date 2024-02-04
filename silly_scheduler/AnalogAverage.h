#ifndef AnalogAverage_h
#define AnalogAverage_h
#include "Arduino.h" 
#include "ScheduledJob.h" 

#define AnalogAverage_bits 14
#define AnalogAverage_minChange 8

class AnalogAverage: public ScheduledJob {
public:
  AnalogAverage(byte pin);
  void setup();
  void loopScheduled();
  unsigned int getValue(); 
  unsigned long delayDurationMicros = 1500;

private:
  byte analogPin;
  unsigned int lastValue;
  unsigned int readingCounter = 1 << AnalogAverage_bits;
  unsigned int readingSum = 0;
};

#endif
