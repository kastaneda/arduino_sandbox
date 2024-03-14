#include <Arduino.h>

#include "loop_job.h"
#include "mqtt_io.h"
#include "debouncer.h"
#include "blinking_led.h"
// TODO FIXME #include "my_servo.h"
// TODO FIXME #include "my_stepper.h"

BlinkingLED myBlinker(LED_BUILTIN);
const int myButtonPin = 2;
Debouncer myButton;
MessageReader myMQTT;

void setup() {
  Serial.begin(9600);
  myMQTT.begin();
  myBlinker.setup();
  myBlinker.runPeriod = 250000; // 250ms
  pinMode(myButtonPin, INPUT_PULLUP);
  myButton.readingSource = []() { return digitalRead(myButtonPin); };
  myButton.onFall = []() { myBlinker.enabled = !myBlinker.enabled; };
  myMQTT.FIXME_testCommand = []() { myBlinker.enabled = !myBlinker.enabled; };
}

void loop() {
  myBlinker.loop();
  myButton.loop();
  myMQTT.loop();
}
