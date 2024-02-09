#include "Arduino.h"
#include "SineWave.h"

const 

// argument: from 0 to 1023
// result: from -255 to 255
int mySine(int angle) {
  int result;
  int multiplier = 1;
  if (angle > 511) {
    multiplier = -1;
    angle -= 512;
  }
  if (angle <= 255) {
    result = SineWave[angle];
  } else {
    result = SineWave[511-angle];
  }
  return result * multiplier;
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}

void repeatOnOff(int repeatCount, int timeOn, int timeOff) {
  for (int repeat = 0; repeat < repeatCount; repeat++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delayMicroseconds(timeOn);
    digitalWrite(LED_BUILTIN, LOW);
    delayMicroseconds(timeOff);
  }
}

void loop() {
  for (int step = 0; step < 1023; step+=8) {
    int stepOn = mySine(step) + 256;
    int stepOff = 512 - stepOn;
    repeatOnOff(50, stepOn, stepOff);
  }  
//  repeatOnOff(100, 100, 900);
//  repeatOnOff(100, 200, 800);
//  repeatOnOff(100, 300, 700);
//  repeatOnOff(100, 400, 600);
//  repeatOnOff(100, 500, 500);
}
