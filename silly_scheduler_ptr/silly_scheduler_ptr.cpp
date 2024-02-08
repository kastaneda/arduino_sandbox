#include "Arduino.h" 

////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////

class Debouncer: public ShouldLoop {
public:
  int stateDebounced = 0;
  unsigned long debounceDelay = 50;

  int (*readingSource)() = 0;
//  void (*onRaise)() = 0;
//  void (*onFall)() = 0;
  void (*onChange)(int state) = 0;

  void loopWhen(unsigned long timeNow);

private:
  int lastReading = 0;
  unsigned long lastDebounceTime = 0;
};

void Debouncer::loopWhen(unsigned long timeNow) {
  if (this->readingSource) {
    int reading = this->readingSource();
    
    if (reading != this->lastReading) {
      this->lastDebounceTime = timeNow;
    }

    if ((timeNow - this->lastDebounceTime) > this->debounceDelay) {
      if (reading != this->stateDebounced) {
        this->stateDebounced = reading;
//        if (!reading && this->onFall) {
//          this->onFall();
//        }
//        if (reading && this->onRaise) {
//          this->onRaise();
//        }
        if (this->onChange) {
          this->onChange(stateDebounced);
        }
      }
    }

    this->lastReading = reading;
  }
}

////////////////////////////////////////////////////////////////////////

class DigitalReader: public ShouldSetup {
public:
  DigitalReader(byte pin);
  void setup();
  int read();

private:
  byte pin;
};

DigitalReader::DigitalReader(byte pin) {
  this->pin = pin;
}

void DigitalReader::setup() {
  pinMode(this->pin, INPUT_PULLUP);
}

int DigitalReader::read() {
  return digitalRead(this->pin);
}

////////////////////////////////////////////////////////////////////////

class ToggleLED: public ShouldSetup {
public:
  ToggleLED(byte pin);
  void setup();
  void toggle();

private:
  byte pin;
  byte state = 0;
};

ToggleLED::ToggleLED(byte pin) {
  this->pin = pin;
}

void ToggleLED::setup() {
  pinMode(this->pin, OUTPUT);
  digitalWrite(this->pin, LOW);
}

void ToggleLED::toggle() {
  this->state = 1 - this->state;
  digitalWrite(this->pin, this->state);
}

////////////////////////////////////////////////////////////////////////

DigitalReader myPin(2);
ToggleLED myLED(LED_BUILTIN);
Debouncer myButton;

void setup() {
  myPin.setup();
  myLED.setup();
  myButton.readingSource = []() { return myPin.read(); };
  myButton.onChange = [](int state) { if (!state) myLED.toggle(); };
}

void loop() {
  myButton.loop();
}
