// Controlling 28BYJ-48 5V stepper motor + ULN2003 driver
// Now with microstepping! :)

// Soft-PWM with LEDs: https://youtu.be/r2MwitaEKHs
// (with delay() instead of delayMicroseconds() and longer pulse duration)

// 28BYJ-48 in action: https://youtu.be/0g9wiJC0UCM

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

// bit 0: pin 1
// bit 1: pin 2
// bit 2: pin 3
// bit 3: pin 4
void setMotorState(byte bitMaskState) {
  for (byte i = 0, j = 1; i < sizeof(motorPins); i++, j <<= 1) {
    digitalWrite(motorPins[i], (bitMaskState & j) ? HIGH : LOW);
  }
}

/*
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
*/

const byte motorStepSequence[4] = {
  B1000,
  B0100,
  B0010,
  B0001
}; // full steps

#define motorStopped 0

#define RotateClockwise 1
#define RotateCounterClockwise -1

// Software-defined PWM
//       _      __     ___    ____   _____
//      | |    |  |   |   |  |    | |
//      | |    |  |   |   |  |    | |
// _____| |____|  |___|   |__|    |_|

#define pulseWidth 300
#define pulseDelta 10

#define microstepDuration pulseWidth              // here: 300 µs
#define microstepCount    pulseWidth / pulseDelta // here: 30
#define oneStepDuration   microstepDuration * microstepCount

/*
void motorStateTransition(byte stateOld, byte stateNew) {
  // no PWM
  setMotorState(stateNew);
  delay(oneStepDuration);
}
*/

void motorStateTransition(byte stateOld, byte stateNew) {
  int delayOld = pulseWidth, delayNew = 0;

  do {
    if (delayOld > 0) {
      setMotorState(stateOld);
      delayMicroseconds(delayOld);
      // delay(delayOld); // XXX debug with LEDs
    }

    if (delayNew > 0) {
      setMotorState(stateNew);
      delayMicroseconds(delayNew);
      // delay(delayNew); // XXX debug with LEDs
    }

    delayOld -= pulseDelta;
    delayNew += pulseDelta;
  } while (delayOld > 0);
}

void motorRotate(unsigned long int rotateSteps, signed char rotateDirection) {
  byte step = 0;
  byte stateOld = motorStopped;
  byte stateNew;

  for (unsigned long int i = 0; i < rotateSteps; i++) {
    stateNew = motorStepSequence[step];
    motorStateTransition(stateOld, stateNew);
    step = (step + rotateDirection) % sizeof(motorStepSequence);
    stateOld = stateNew;
  }

  setMotorState(motorStopped);
}

void loop() {
  motorRotate(4096, RotateClockwise);
  delay(500);
  motorRotate(4096, RotateCounterClockwise);
  delay(500);
}
