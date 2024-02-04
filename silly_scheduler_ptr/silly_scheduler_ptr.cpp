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

class ButtonDebouncer: /* public ShouldSetup, */ public ShouldLoop {
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
        if (reading && this->onKeyDown) {
          this->onKeyDown();
        }
        if (!reading && this->onKeyUp) {
          this->onKeyUp();
        }
      }
    }

    this->lastButtonState = reading;
  }
}

int buttonReadingSource() {
  return digitalRead(2);
}

bool ledState = 0;
void ledToggle() {
  ledState = 1 - ledState;
  digitalWrite(LED_BUILTIN, ledState);
}

ButtonDebouncer btn1;

void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  btn1.readingSource = buttonReadingSource;
  //btn1.onKeyUp = ledToggle;
  btn1.onKeyDown = ledToggle;
  //btn1.setup();
}

void loop() {
  btn1.loop();
}
