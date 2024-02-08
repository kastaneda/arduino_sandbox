#include "Arduino.h"

class ShouldSetup {
public:
  virtual void setup() = 0;
};

class ShouldLoop {
public:
  virtual void loopWhen(unsigned long timeNow) = 0;
  void loop();
};

void ShouldLoop::loop() {
  this->loopWhen(micros());
}

class ScheduledLoop: public ShouldLoop {
public:
  unsigned long runPeriod = 1000000;
  void loopWhen(unsigned long timeNow);

protected:
  virtual void runScheduled() = 0;

private:
  unsigned long lastRun = 0;
};

void ScheduledLoop::loopWhen(unsigned long timeNow) {
  if ((timeNow - this->lastRun) >= this->runPeriod) {
    this->runScheduled();
    this->lastRun = timeNow;
  }
}

class BlinkingLED: public ShouldSetup, public ScheduledLoop {
public:
  BlinkingLED(byte pin);
  void setup();
  void runScheduled();
  bool enabled = true;

private:
  byte pin;
  bool state = false;
};

BlinkingLED::BlinkingLED(byte pin) {
  this->pin = pin;
}

void BlinkingLED::setup() {
  pinMode(this->pin, OUTPUT);
  digitalWrite(this->pin, LOW);
}

void BlinkingLED::runScheduled() {
  this->state = this->enabled && !this->state;
  digitalWrite(this->pin, this->state ? HIGH : LOW);
}

BlinkingLED myBlinker(LED_BUILTIN);

void setup() {
  myBlinker.setup();
  myBlinker.runPeriod = 250000;
}

void loop() {
  myBlinker.loop();
}
