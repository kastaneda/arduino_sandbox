
#define debug

#define moveForward       1
#define moveBackward     -1
#define motorStopped      0

#define cmd_outputPinHigh 129
#define cmd_outputPinLow  130
#define cmd_motorForward  193
#define cmd_motorBackward 194
#define cmd_setMotorDelay 196

const byte outputPins[] = { 4, 5, 6, 7, 13 };

const byte motorPins[] = { 8, 9, 10, 11 };
const byte motorStepSequence[] = { B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001 };

unsigned int motorStepDelay = 3000;

void setMotorState(byte bitMaskState) {
  for (byte i = 0, j = 1; i < sizeof(motorPins); i++, j <<= 1) {
    digitalWrite(motorPins[i], (bitMaskState & j) ? HIGH : LOW);
  }
}

void motorRotate(unsigned long int rotateSteps, signed char rotateDirection) {
  byte step = 0;

  for (unsigned long int i = 0; i < rotateSteps; i++) {
    setMotorState(motorStepSequence[step]);
    delayMicroseconds(motorStepDelay);
    step = (step + rotateDirection) % sizeof(motorStepSequence);
  }

  setMotorState(motorStopped);
}

void setup() {
  Serial.begin(9600);

  for (byte i = 0; i < sizeof(outputPins); i++) {
    pinMode(outputPins[i], OUTPUT);
    digitalWrite(outputPins[i], LOW);
  }

  for (byte i = 0; i < sizeof(motorPins); i++) {
    pinMode(motorPins[i], OUTPUT);
    digitalWrite(motorPins[i], LOW);
  }
}

void loop() {
  unsigned int cmd;
  unsigned long int arg1;

  if (Serial.available()) {
    cmd = Serial.parseInt();
    arg1 = Serial.parseInt();

    while (Serial.available())
      Serial.read();

#ifdef debug
    Serial.print("Command=");
    Serial.print(cmd);
    Serial.print(" arg1=");
    Serial.println(arg1);
#endif

    switch (cmd) {
      case cmd_outputPinHigh:
      case cmd_outputPinLow:
        for (byte i = 0; i < sizeof(outputPins); i++) {
          if (outputPins[i] == arg1) {
#ifdef debug
            Serial.print("Pin ");
            Serial.print(arg1);
            Serial.print(" set ");
            if (cmd == cmd_outputPinHigh) {
              Serial.println("HIGH");
            } else {
              Serial.println("LOW");
            }
#endif
            digitalWrite(outputPins[i], (cmd == cmd_outputPinHigh) ? HIGH : LOW);
          }
        }
        break;

      case cmd_motorForward:
      case cmd_motorBackward:
#ifdef debug
        Serial.print("Motor go ");
        if (cmd == cmd_motorForward) {
          Serial.print("forward");
        } else {
          Serial.print("backward");
        }
        Serial.print(", steps=");
        Serial.println(arg1);
#endif
        motorRotate(arg1, (cmd == cmd_motorForward) ? moveForward : moveBackward);
        break;

      case cmd_setMotorDelay:
#ifdef debug
        Serial.print("Motor step delay: old=");
        Serial.print(motorStepDelay);
        Serial.print(", new=");
        Serial.println(arg1);
#endif
        motorStepDelay = arg1;
    }
  }
}
