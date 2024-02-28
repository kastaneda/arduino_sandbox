#include "Arduino.h"

////////////////////////////////////////////////////////////////////////

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

BlinkingLED myBlinker(LED_BUILTIN);
const int myButtonPin = 2;
Debouncer myButton;

////////////////////////////////////////////////////////////////////////

// atmega168

// a micros() call costs ~3 usec

// min: 0, max: 16, avg: 3.11
// min: 0, max: 12, avg: 3.10
// min: 0, max: 12, avg: 3.11
// min: 0, max: 16, avg: 3.11
// min: 0, max: 12, avg: 3.11
unsigned long test1() {
  unsigned long t1, t2;
  t1 = micros();
  t2 = micros();
  return t2 - t1;
}

// calling BlinkingLED::loop() costs ~10 usec

// min: 8, max: 24, avg: 9.88
// min: 8, max: 24, avg: 9.87
// min: 8, max: 24, avg: 9.87
// min: 8, max: 24, avg: 9.88
// min: 8, max: 20, avg: 9.87

// class ShouldLoop
// when I replaced "void loop();" to the "virtual void loop() final;"
// it becomes notably slower

// min: 8, max: 28, avg: 11.99
// min: 8, max: 24, avg: 11.99
// min: 8, max: 20, avg: 12.00
// min: 8, max: 20, avg: 12.00
// min: 8, max: 20, avg: 12.00

unsigned long test2() {
  unsigned long t1, t2;
  t1 = micros();
  myBlinker.loop();
  t2 = micros();
  return t2 - t1;
}

// haha, 9600 is really sloooow, but well, why not

// min: 2064, max: 2076, avg: 2073.32
// min: 2064, max: 2076, avg: 2073.24
// min: 2064, max: 2076, avg: 2072.88
// min: 2064, max: 2076, avg: 2073.28
// min: 2064, max: 2080, avg: 2073.36
unsigned long test3() {
  unsigned long t1, t2;
  t1 = micros();
  Serial.print(' ');
  Serial.print('\b');
  t2 = micros();
  return t2 - t1;
}

// fair enough

// min: 20, max: 36, avg: 23.24
// min: 20, max: 36, avg: 23.25
// min: 20, max: 40, avg: 23.26
// min: 20, max: 36, avg: 23.26
// min: 20, max: 32, avg: 23.27
unsigned long test4() {
  unsigned long t1, t2;
  t1 = micros();
  myBlinker.loop();
  myButton.loop();
  t2 = micros();
  return t2 - t1;
}

void setup() {
  Serial.begin(9600);
  myBlinker.setup();
  myBlinker.runPeriod = 250000; // 250ms
  pinMode(myButtonPin, INPUT_PULLUP);
  myButton.readingSource = []() { return digitalRead(myButtonPin); };
  myButton.onFall = []() { myBlinker.enabled = !myBlinker.enabled; };
}

void loop() {
  unsigned long t, t_min, t_max, t_avg;
  const unsigned long test_count = 10000;

  t_min = t_max = t_avg = 0;
  for (unsigned int i = 0; i < test_count; i++) {
    t = test4();
    t_avg += t;
    if (i) {
      t_min = min(t, t_min);
      t_max = max(t, t_max);
    } else {
      t_min = t_max = t;
    }
  }

  Serial.print("min: ");    Serial.print(t_min, DEC);
  Serial.print(", max: ");  Serial.print(t_max, DEC);
  Serial.print(", avg: ");  Serial.println((float) t_avg / test_count);
}
