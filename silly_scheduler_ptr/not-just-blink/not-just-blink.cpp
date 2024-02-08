#include "Arduino.h"

class ShouldSetup {
public:
  virtual void setup() = 0;
};

class ShouldLoop {
public:
  virtual void loopAt(unsigned long timeNow) = 0;
  void loop();
};

void ShouldLoop::loop() {
  this->loopAt(micros());
}

class ScheduledLoop: public ShouldLoop {
public:
  unsigned long runPeriod = 1000000;
  void loopAt(unsigned long timeNow);

protected:
  virtual void runScheduled() = 0;

private:
  unsigned long lastRun = 0;
};

void ScheduledLoop::loopAt(unsigned long timeNow) {
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

class Debouncer: public ShouldLoop {
public:
  int stateDebounced = 0;
  unsigned long debounceDelay = 50000; // 50ms

  int (*readingSource)() = 0;
  void (*onRaise)() = 0;
  void (*onFall)() = 0;
  void (*onChange)(int state) = 0;

  void loopAt(unsigned long timeNow);

private:
  int lastReading = 0;
  unsigned long lastDebounceTime = 0;
};

void Debouncer::loopAt(unsigned long timeNow) {
  if (this->readingSource) {
    int reading = this->readingSource();

    if (reading != this->lastReading) {
      this->lastDebounceTime = timeNow;
    }

    if ((timeNow - this->lastDebounceTime) >= this->debounceDelay) {
      if (reading != this->stateDebounced) {
        this->stateDebounced = reading;
        if (this->onFall && !reading) this->onFall();
        if (this->onRaise && reading) this->onRaise();
        if (this->onChange) this->onChange(reading);
      }
    }

    this->lastReading = reading;
  }
}

const int myButtonPin = 2;
Debouncer myButton;
BlinkingLED myBlinker(LED_BUILTIN);

void setup() {
  pinMode(myButtonPin, INPUT_PULLUP);
  myBlinker.setup();
  myBlinker.runPeriod = 250000;
  myButton.readingSource = []() { return digitalRead(myButtonPin); };
  myButton.onFall = []() { myBlinker.enabled = !myBlinker.enabled; };
}

void loop() {
  myButton.loop();
  myBlinker.loop();
}
