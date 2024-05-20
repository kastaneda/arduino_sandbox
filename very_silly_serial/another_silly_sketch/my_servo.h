#ifndef MY_SERVO_H
#define MY_SERVO_H

#include <Arduino.h>

#include "Servo.h"
// probably it should be <Servo.h>
// and I should know more about building Arduino libraries

#include "loop_job.h"

class MyServo: public ScheduledLoop {
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
