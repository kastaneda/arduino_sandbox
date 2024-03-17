#include <Arduino.h>

#include "loop_job.h"
#include "mqtt_io.h"
#include "debouncer.h"
#include "blinking_led.h"
// TODO FIXME #include "my_servo.h"
// TODO FIXME #include "my_stepper.h"

BlinkingLED myBlinker(LED_BUILTIN);

const uint8_t myButtonPin = 2;
Debouncer myButton;

MessageHub mqtt;

TopicSubscription topics[] = {
  {
    "dev/board05/led/set",
    [](char *payload) {
      myBlinker.enabled = (payload[0] == '1');
    }
  }
};

void setup() {
  Serial.begin(9600);

  mqtt.begin();
  mqtt.subscriptions = topics;
  mqtt.subscriptionsCount = sizeof(topics) / sizeof(topics[0]);

  myBlinker.setup();
  myBlinker.runPeriod = 250000; // 250ms

  pinMode(myButtonPin, INPUT_PULLUP);
  myButton.readingSource = []() {
    return digitalRead(myButtonPin);
  };
  myButton.onFall = []() {
    myBlinker.enabled = !myBlinker.enabled;
    mqtt.send("dev/board05/led", myBlinker.enabled ? 1 : 0);
  };
}

void loop() {
  myBlinker.loop();
  myButton.loop();
  mqtt.loop();
}
