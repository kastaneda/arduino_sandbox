#ifndef MY_SERVO_H
#define MY_SERVO_H

#include <Arduino.h>
// #include <Servo.h>

#include "Servo.h"

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
