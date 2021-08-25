const byte motorPins[4] = {
  8,  // Blue   - 28BYJ48 pin 1
  9,  // Pink   - 28BYJ48 pin 2
  10, // Yellow - 28BYJ48 pin 3
  11  // Orange - 28BYJ48 pin 4
};    // Red    - 28BYJ48 pin 5 (VCC)

void setup() {
  for (byte i = 0; i < sizeof(motorPins); i++) {
    pinMode(motorPins[i], OUTPUT);
  }
}

void setMotorState(byte bitMaskState) {
  for (byte i = 0, j = 1; i < sizeof(motorPins); i++, j <<= 1) {
    digitalWrite(motorPins[i], (bitMaskState & j) ? HIGH : LOW);
  }
}

const byte motorStepSequence[8] = {
  B1000,
  B1100,
  B0100,
  B0110,
  B0010,
  B0011,
  B0001,
  B1001
};

/*
const byte motorStepSequence[4] = {
  B1000,
  B0100,
  B0010,
  B0001,
};
*/

#define motorStopped 0
#define RotateClockwise 1
#define RotateCounterClockwise -1

void motorRotate(unsigned int rotateSteps, signed char rotateDirection) {
  const unsigned int stepDelay = 2500;
  byte step = 0;

  for (unsigned int i = 0; i < rotateSteps; i++) {
    setMotorState(motorStepSequence[step]);
    // delayMicroseconds(stepDelay);
    delay(stepDelay); // FIXME XXX only to debug
    step = (step + rotateDirection) % sizeof(motorStepSequence);
  }

  setMotorState(motorStopped);
}

void loop() {
  motorRotate(4096, RotateClockwise);
  delay(500);
  motorRotate(4096, RotateCounterClockwise);
  delay(500);
}
