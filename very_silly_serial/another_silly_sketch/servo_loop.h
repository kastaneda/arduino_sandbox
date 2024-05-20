#ifndef SERVO_LOOP_H
#define SERVO_LOOP__H

#include <Arduino.h>

#include "Servo.h"
// probably it should be <Servo.h>
// and I should know more about building Arduino libraries

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
