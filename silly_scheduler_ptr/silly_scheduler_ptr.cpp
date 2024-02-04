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

class ButtonDebouncer: public ShouldLoop {
public:
  int buttonState = 0;
  unsigned long debounceDelay = 50;

  int (*readingSource)() = 0;
  void (*onKeyDown)() = 0;
  void (*onKeyUp)() = 0;

  void loopWhen(unsigned long timeNow);

private:
  int lastButtonState = 0;
  unsigned long lastDebounceTime = 0;
};

void ButtonDebouncer::loopWhen(unsigned long timeNow) {
  if (this->readingSource) {
    int reading = this->readingSource();
    
    if (reading != this->lastButtonState) {
      this->lastDebounceTime = timeNow;
    }

    if ((timeNow - this->lastDebounceTime) > this->debounceDelay) {
      if (reading != this->buttonState) {
        this->buttonState = reading;
        // It's pull-up, so LOW means button is pressed, HIGH elsewhere
        if (!reading && this->onKeyDown) {
          this->onKeyDown();
        }
        if (reading && this->onKeyUp) {
          this->onKeyUp();
        }
      }
    }

    this->lastButtonState = reading;
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
ButtonDebouncer myButton;

int inputLink() {
  return myPin.read();
}

void outputLink() {
  myLED.toggle();
}

void setup() {
  myPin.setup();
  myLED.setup();

  // TODO FIXME
  // Can I somehow use here a class member of specific instance?
  myButton.readingSource = inputLink;
  myButton.onKeyDown = outputLink;

  // error: cannot convert ‘ToggleLED::toggle’ from type ‘void (ToggleLED::)()’ to type ‘void (*)()’
  // myButton.onKeyDown = myLED.toggle;
}

void loop() {
  myButton.loop();
}
