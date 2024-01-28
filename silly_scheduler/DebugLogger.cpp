#include "Arduino.h" 
#include "DebugLogger.h" 

DebugLogger::DebugLogger(int FIXME) {
  this->delayDurationMicros = 1000000; // 1 s
  this->lastRunMicros = micros();
}

void DebugLogger::setValue(long value) {
  this->debugValue = value;
}

void DebugLogger::setup() {
  Serial.begin(9600);
}

void DebugLogger::loopScheduled() {
  if (Serial) {
    Serial.println(this->debugValue);
  }
}
