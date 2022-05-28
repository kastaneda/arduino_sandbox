// Controlling 28BYJ-48 5V stepper motor + ULN2003 driver
// Now with microstepping! :)

// Soft-PWM with LEDs: https://youtu.be/r2MwitaEKHs
// (with delay() instead of delayMicroseconds() and longer pulse duration)

// 28BYJ-48 in action: https://youtu.be/0g9wiJC0UCM

const byte motorPins[4] = {
  5,  // Blue   - 28BYJ48 pin 1
  6,  // Pink   - 28BYJ48 pin 2
  7,  // Yellow - 28BYJ48 pin 3
  8   // Orange - 28BYJ48 pin 4
};    // Red    - 28BYJ48 pin 5 (VCC)

void setup() {
  for (byte i = 0; i < sizeof(motorPins); i++) {
    pinMode(motorPins[i], OUTPUT);
  }
}

// bit 0: pin 1
// bit 1: pin 2
// bit 2: pin 3
// bit 3: pin 4
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
}; // half steps

/*
const byte motorStepSequence[4] = {
  B1000,
  B0100,
  B0010,
  B0001
}; // full steps
*/

#define motorStopped 0

#define RotateClockwise 1
#define RotateCounterClockwise -1

// Software-defined PWM
//       _      __     ___    ____   _____
//      | |    |  |   |   |  |    | |
//      | |    |  |   |   |  |    | |
// _____| |____|  |___|   |__|    |_|

void setMotorStateAndDelay(byte motorState, unsigned int delayDuration) {
  setMotorState(motorState);
  delayMicroseconds(delayDuration);
  // delay(delayDuration); // XXX debug with LEDs
}

void motorOnePulseCycle(byte stateOld, byte stateNew, int onePulseWidth, int subPartNew) {
  subPartNew = min(onePulseWidth, subPartNew); // sanity check
  int subPartOld = onePulseWidth - subPartNew;

  if (subPartOld > subPartNew) {
    // old state prevail
    if (subPartNew > 0) {
      setMotorStateAndDelay(stateOld | stateNew, subPartNew);
      setMotorStateAndDelay(stateOld, onePulseWidth - (subPartNew << 1));
      setMotorStateAndDelay(stateOld & stateNew, subPartNew);
    } else {
      setMotorStateAndDelay(stateOld, onePulseWidth);
    }
  } else if (subPartOld < subPartNew) {
    // new state prevail
    if (subPartOld > 0) {
      setMotorStateAndDelay(stateOld | stateNew, subPartOld);
      setMotorStateAndDelay(stateNew, onePulseWidth - (subPartOld << 1));
      setMotorStateAndDelay(stateOld & stateNew, subPartOld);
    } else {
      setMotorStateAndDelay(stateNew, onePulseWidth);
    }
  } else {
    // equal
    setMotorStateAndDelay(stateOld | stateNew, subPartOld);
    setMotorStateAndDelay(stateOld & stateNew, subPartOld);
  }
}

#define pulseWidth 81
#define pulseDelta 9

void motorStateTransition(byte stateOld, byte stateNew) {
  int onePulseWidth = pulseWidth, subPartNew = 0, subDelta = pulseDelta;
  do {
    motorOnePulseCycle(stateOld, stateNew, onePulseWidth, subPartNew);
    subPartNew += subDelta;
  } while (subPartNew < onePulseWidth);
}

void motorStateTransitionDumb(byte stateOld, byte stateNew) {
  setMotorStateAndDelay(stateNew, 1100); // 2.2 ms for one full step
}

byte useDumbMode = 0;

void motorRotate(unsigned long int rotateSteps, signed char rotateDirection) {
  byte step = 0;
  byte stateOld = motorStopped;
  byte stateNew;

  for (unsigned long int i = 0; i < rotateSteps; i++) {
    stateNew = motorStepSequence[step];
    if (useDumbMode) {
      motorStateTransitionDumb(stateOld, stateNew);
    } else {
      motorStateTransition(stateOld, stateNew);
    }
    step = (step + rotateDirection) % sizeof(motorStepSequence);
    stateOld = stateNew;
  }

  setMotorState(motorStopped);
}

void loop() {
  useDumbMode = 0;

  motorRotate(4096, RotateClockwise);
  delay(500);
  motorRotate(4096, RotateCounterClockwise);
  delay(500);

  useDumbMode = 1;

  motorRotate(4096, RotateClockwise);
  delay(500);
  motorRotate(4096, RotateCounterClockwise);
  delay(500);
}
