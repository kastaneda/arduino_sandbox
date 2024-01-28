#ifndef BlinkingLED_h
#define BlinkingLED_h
#include "Arduino.h" 
#include "ScheduledJob.h" 

class BlinkingLED: public ScheduledJob {
public:
  BlinkingLED(int pin);
  void setBlinkEnabled(bool enabled);
  void setup();
  void loopScheduled();

private:
  int ledPin;
  bool blinkEnabled;
  bool ledState;
};

#endif
