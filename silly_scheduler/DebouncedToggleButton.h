#ifndef DebouncedToggleButton_h
#define DebouncedToggleButton_h
#include "Arduino.h" 
#include "PeriodicJob.h" 

class DebouncedToggleButton: public PeriodicJob {
public:
  DebouncedToggleButton(int pin);
  bool getState();
  void setup();
  void loopWhen(unsigned long timeNowMicros);

private:
  bool toggleState;
  int buttonPin;
  int buttonState;
  int lastButtonState;
  unsigned long lastDebounceTime;
  unsigned long debounceDelay;
};

#endif
