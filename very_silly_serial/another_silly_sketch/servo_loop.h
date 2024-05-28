#ifndef SERVO_LOOP_H
#define SERVO_LOOP__H

#include <Arduino.h>
#include <Servo.h>

#include "void_loop.h"

class ServoLoop: public ScheduledLoop {
public:
  void setup(uint8_t pin);
  void write(int angle);

protected:
  void runScheduled();

private:
  uint8_t pin;
  Servo servo;
  bool attached = false;
  int angle = 90;
};

#endif
