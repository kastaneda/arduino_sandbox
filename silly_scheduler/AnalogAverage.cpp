#include "Arduino.h" 
#include "AnalogAverage.h" 

AnalogAverage::AnalogAverage(byte pin) {
  this->analogPin = pin;
}

unsigned int AnalogAverage::getValue() {
  return this->lastValue;
}

void AnalogAverage::setup() {
  pinMode(this->analogPin, INPUT);
  this->lastValue = analogRead(this->analogPin);
}

void AnalogAverage::loopScheduled() {
  this->readingSum += analogRead(this->analogPin);
  this->readingCounter--;
  if (this->readingCounter == 0) {
    unsigned int nextValue;
    nextValue = this->readingSum >> AnalogAverage_bits;
    if (abs(nextValue - this->lastValue) >= AnalogAverage_minChange) {
      this->lastValue = nextValue;
    }
    this->lastValue = this->readingSum >> AnalogAverage_bits;
    this->readingCounter = 1 << AnalogAverage_bits;
    this->readingSum = 0;
  }
}
