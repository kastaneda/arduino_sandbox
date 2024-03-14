#include "debouncer.h"

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
