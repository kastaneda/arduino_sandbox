#include "Arduino.h" 
#include "DebouncedToggleButton.h" 

DebouncedToggleButton::DebouncedToggleButton(int pin) {
  this->buttonPin = pin;
  this->toggleState = true;       // turned on by default
  this->buttonState = HIGH;       // HIGH == not pressed (pull-up)
  this->lastButtonState = HIGH;
  this->debounceDelay = 50000;    // 50 ms
  this->lastDebounceTime = micros();
}

bool DebouncedToggleButton::getState() {
  return this->toggleState;
}

void DebouncedToggleButton::setup() {
  pinMode(this->buttonPin, INPUT_PULLUP);
}

void DebouncedToggleButton::loopWhen(unsigned long timeNowMicros) {
  int reading = digitalRead(this->buttonPin);

  if (reading != this->lastButtonState) {
    this->lastDebounceTime = timeNowMicros;
  }

  if ((timeNowMicros - this->lastDebounceTime) > this->debounceDelay) {
    if (reading != this->buttonState) {
      this->buttonState = reading;
      if (this->buttonState == HIGH) {
        this->toggleState = ! this->toggleState;
        // TODO: maybe call some onclick pointer function?
      }
    }
  }

  this->lastButtonState = reading;
}
