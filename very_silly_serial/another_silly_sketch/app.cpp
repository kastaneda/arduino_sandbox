#include <Arduino.h>

#include "loop_job.h"
#include "mqtt_io.h"
#include "debouncer.h"
#include "blinking_led.h"
#include "beeper.h"
// TODO FIXME #include "my_servo.h"
// TODO FIXME #include "my_stepper.h"

BlinkingLED myBlinker(LED_BUILTIN);
const uint8_t myButtonPin = 2;
Debouncer myButton;
Beeper myBeeper(5);
MessageHub mqtt;

TopicSubscription topics[] = {
  {
    "dev/board05/led/set",
    [](char *payload) {
      myBeeper.beep();
      myBlinker.enabled = (payload[0] == '1');
    }
  },
  {
    "dev/board05/beeper/set",
    [](char *payload) {
      unsigned long duration = 0;
      uint8_t i = 0;
      while (payload[i]) {
        if ((payload[i] >= '0') && (payload[i] <= '9'))
          duration = duration * 10 + (payload[i] - '0');
        i++;
      }
      myBeeper.beep(duration);
    }
  }
};

class MyAnalogReader: public ScheduledLoop {
public:
  uint8_t pin;
protected:
  void runScheduled() {
    if (Serial.availableForWrite() > 20) {
      mqtt.send("dev/board05/A0", analogRead(this->pin));
    }
  }
} myA0;

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
    myBeeper.beep();
    mqtt.send("dev/board05/led", myBlinker.enabled ? 1 : 0);
  };

  pinMode(A0, INPUT);
  myA0.pin = A0;
  myA0.runPeriod = 150000; // 150ms

  myBeeper.setup();
}

void loop() {
  myBlinker.loop();
  myButton.loop();
  mqtt.loop();
  myA0.loop();
  myBeeper.loop();
}
