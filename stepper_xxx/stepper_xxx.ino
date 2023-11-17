const byte motorPins[] = { 8, 9, 10, 11 };

// https://en.wikipedia.org/wiki/Stepper_motor#Phase_current_waveforms
// https://upload.wikimedia.org/wikipedia/commons/8/85/Drive.png

////////////////////////////////////////////////////////////////////////
//
// Wave drive
//
//    _______                         _______                         __
// __|       |_______________________|       |_______________________|
//
//            _______                         _______
// __________|       |_______________________|       |__________________
//
//                    _______                         _______
// __________________|       |_______________________|       |__________
//
// __                         _______                         _______
//   |_______________________|       |_______________________|       |__
//

const byte sequence_WaveDrive[] = {
  B1000,
  B0100,
  B0010,
  B0001
};

////////////////////////////////////////////////////////////////////////
//
// Full-step drive
//
//    _______________                 _______________                 __
// __|               |_______________|               |_______________|
//
//            _______________                 _______________
// __________|               |_______________|               |__________
//
//                    _______________                 _______________
// __________________|               |_______________|               |__
//
// __________                 _______________                 __________
//           |_______________|               |_______________|
//

const byte sequence_FullStepDrive[] = {
  B1100,
  B0110,
  B0011,
  B1001
};


////////////////////////////////////////////////////////////////////////
//
// Half-step drive
//
//     ___________                      ___________
// ___|           |____________________|           |____________________
//
//             ___________                      ___________
// ___________|           |____________________|           |____________
//
//                     ___________                      ___________
// ___________________|           |____________________|           |____
//
// ______                      ___________                      ________
//       |____________________|           |____________________|
//

const byte sequence_HalfStepDrive[] = {
  B1000,
  B1100,
  B0100,
  B0110,
  B0010,
  B0011,
  B0001,
  B1001
};

////////////////////////////////////////////////////////////////////////

#define moveForward 1
#define moveBackward -1
#define motorStopped 0

// #define motorStepSequence sequence_WaveDrive
#define motorStepSequence sequence_FullStepDrive
// #define motorStepSequence sequence_HalfStepDrive
#define motorStepDelay 2000

byte motorStep = 0;

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

void motorRotate(unsigned long int rotateSteps, signed char rotateDirection) {
  for (unsigned long int i = 0; i < rotateSteps; i++) {
    motorStep = (motorStep + rotateDirection) % sizeof(motorStepSequence);
    setMotorState(motorStepSequence[motorStep]);
    delayMicroseconds(motorStepDelay);
  }
  setMotorState(motorStopped);
}

void loop() {
  motorRotate(2048, moveForward);
  delay(500);
  motorRotate(2048, moveBackward);
  delay(500);
}
