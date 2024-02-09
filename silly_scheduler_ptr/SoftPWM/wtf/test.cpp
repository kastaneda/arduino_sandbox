#include <iostream>
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

int main() {
  for (int step = 0; step < 1024; step+=8) {
    int pulseOn = mySine(step) + 256;
    int pulseOff = 512 - pulseOn;
    std::cout << pulseOn << " " << pulseOff << std::endl;
  }
}
