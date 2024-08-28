#include <Arduino.h>

const uint8_t myPins[] = {
   9,   // unit 1, red          index = 0       bitmask = 0b00000001
  10,   // unit 1, yellow       index = 1       bitmask = 0b00000010
  11,   // unit 1, green        index = 2       bitmask = 0b00000100
  A2,   // unit 2, red          index = 3       bitmask = 0b00001000
  A1,   // unit 2, yellow       index = 4       bitmask = 0b00010000
  A0,   // unit 2, green        index = 5       bitmask = 0b00100000
  8,    // unit 1 ground (open drain), always LOW
  A3    // unit 2 ground (open drain), always LOW
};

struct myState {
  uint8_t bitmask;
  uint8_t duration;
};

const myState mySequence[] = {
  { 0b00001001, 3 },  // unit 1: red              unit 2: red
  { 0b00001011, 3 },  // unit 1: red and yellow   unit 2: red
  { 0b00001100, 15 }, // unit 1: green            unit 2: red
  { 0b00001000, 1 },  // unit 1: ---              unit 2: red
  { 0b00001100, 1 },  // unit 1: green            unit 2: red
  { 0b00001000, 1 },  // unit 1: ---              unit 2: red
  { 0b00001100, 1 },  // unit 1: green            unit 2: red
  { 0b00001000, 1 },  // unit 1: ---              unit 2: red
  { 0b00001100, 1 },  // unit 1: green            unit 2: red
  { 0b00001010, 3 },  // unit 1: yellow           unit 2: red
  { 0b00001001, 3 },  // unit 1: red              unit 2: red
  { 0b00011001, 3 },  // unit 1: red              unit 2: red and yellow
  { 0b00100001, 15 }, // unit 1: red              unit 2: green
  { 0b00000001, 1 },  // unit 1: red              unit 2: ---
  { 0b00100001, 1 },  // unit 1: red              unit 2: green
  { 0b00000001, 1 },  // unit 1: red              unit 2: ---
  { 0b00100001, 1 },  // unit 1: red              unit 2: green
  { 0b00000001, 1 },  // unit 1: red              unit 2: ---
  { 0b00100001, 1 },  // unit 1: red              unit 2: green
  { 0b00010001, 3 }   // unit 1: red              unit 2: yellow
};

uint8_t currentStep = 0;

void setup() {
  for (uint8_t i = 0; i < sizeof(myPins); i++) {
    pinMode(myPins[i], OUTPUT);
    digitalWrite(myPins[i], LOW);
  }
}

void loop() {
  uint8_t currentBitmask, currentDuration;

  currentBitmask = mySequence[currentStep].bitmask;
  for (uint8_t i = 0; i < sizeof(myPins); i++) {
    uint8_t bitInMask = (1<<i);
    bool bitFound = (bool) (currentBitmask & bitInMask);
    digitalWrite(myPins[i], bitFound ? HIGH : LOW);
  }

  currentDuration = mySequence[currentStep].duration;
  delay(currentDuration * 1000);

  currentStep++;
  if (currentStep >= (sizeof(mySequence) / sizeof(mySequence[0])))
    currentStep = 0;
}
