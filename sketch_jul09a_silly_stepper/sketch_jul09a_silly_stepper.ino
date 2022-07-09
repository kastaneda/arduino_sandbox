// My 28BYJ-48 5v can do ~20 RPM, huh

#define moveForward 1
#define moveBackward -1
#define motorStopped 0

const byte motorPins[] = { 8, 9, 10, 11 };

void setup() {
  for (byte i = 0; i < sizeof(motorPins); i++) {
    pinMode(motorPins[i], OUTPUT);
    digitalWrite(motorPins[i], LOW);
  }
}

void setMotorState(byte bitMaskState) {
  for (byte i = 0, j = 1; i < sizeof(motorPins); i++, j <<= 1) {
    digitalWrite(motorPins[i], (bitMaskState & j) ? HIGH : LOW);
  }
}

const byte motorStepSequence[] = { B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001 };
#define motorStepSequenceMask 7

#define motorStepDelayMax 2500    // slow and stable movement
#define motorStepDelayMin 700     // minimum delay, maximum speed (~20 RPM)
#define motorStepDelayDelta 10    // how fast we go from 2500 to 700

unsigned int motorStepDelay;

byte motorStep = 0;

void motorRotate(unsigned long int rotateSteps, signed char rotateDirection) {
  motorStepDelay = motorStepDelayMax;

  for (unsigned long int i = 0; i < rotateSteps; i++) {
    motorStep = (motorStep + rotateDirection) & motorStepSequenceMask;
    setMotorState(motorStepSequence[motorStep]);
    delayMicroseconds(motorStepDelay);
    if (motorStepDelay > motorStepDelayMin) {
      motorStepDelay -= motorStepDelayDelta;
    }
  }

  setMotorState(motorStopped);
}


void loop() {
  motorRotate(4096, moveForward);
  delay(500);
  motorRotate(4096, moveBackward);
  delay(500);
}
