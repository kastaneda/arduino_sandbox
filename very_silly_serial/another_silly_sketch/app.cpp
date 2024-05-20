#include <Arduino.h>

#include "void_loop.h"
#include "mqtt_io.h"
#include "debouncer.h"
#include "blinking_led.h"
#include "beeper.h"
#include "servo_loop.h"
#include "stepper_loop.h"

BlinkingLED myBlinker12, myBlinker13;
const uint8_t myButtonPin = 2;
Debouncer myButton;
Beeper myBeeper;
StepperLoop myStepper;
ServoLoop myServo;

MessageHub mqtt;

TopicSubscription topics[] = {
  {
    "dev/board05/led12/set",
    [](char *payload) {
      myBeeper.beep();
      myBlinker12.enabled = (payload[0] == '1');
    }
  },
  {
    "dev/board05/led13/set",
    [](char *payload) {
      myBeeper.beep();
      myBlinker13.enabled = (payload[0] == '1');
    }
  },
  {
    "dev/board05/stepper/set",
    [](char *payload) {
      long target = 0;
      uint8_t sign = 1;
      uint8_t i = 0;
      if (payload[i] == '-') {
        sign = -1;
        i++;
      }
      while (payload[i]) {
        if ((payload[i] >= '0') && (payload[i] <= '9'))
          target = target * 10 + (payload[i] - '0');
        i++;
      }
      myStepper.setTargetStep(target * sign);
      myBeeper.beep(10000);
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
  },
  {
    "dev/board05/servo/set",
    [](char *payload) {
      int angle = 0;
      uint8_t i = 0;
      while (payload[i]) {
        if ((payload[i] >= '0') && (payload[i] <= '9'))
          angle = angle * 10 + (payload[i] - '0');
        i++;
      }
      myServo.write(angle);
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

class MyStepperReporter: public ScheduledLoop {
protected:
  long prevReporting = -1;
  void runScheduled() {
    long reporting;
    reporting = myStepper.getCurrentStep();
    if (reporting != this->prevReporting) {
      this->prevReporting = reporting;
      mqtt.send("dev/board05/stepper", reporting);
    }
  }
} myStepperTelemetry;

void setup() {
  Serial.begin(9600);

  mqtt.begin();
  mqtt.subscriptions = topics;
  mqtt.subscriptionsCount = sizeof(topics) / sizeof(topics[0]);

  myBlinker12.setup(12);
  myBlinker12.runPeriod = 333333; // 333ms hehehe

  myBlinker13.setup(13);
  myBlinker13.runPeriod = 250000; // 250ms

  pinMode(myButtonPin, INPUT_PULLUP);
  myButton.readingSource = []() {
    return digitalRead(myButtonPin);
  };
  myButton.onFall = []() {
    myBlinker12.enabled = !myBlinker12.enabled;
    myBeeper.beep();
    mqtt.send("dev/board05/led12", myBlinker12.enabled ? 1 : 0);
  };

  pinMode(A0, INPUT);
  //analogReference(INTERNAL); // on USB it makes only worse
  myA0.pin = A0;
  myA0.runPeriod = 400000; // 400ms

  myBeeper.setup(5);

  myStepper.setup(8, 9, 10, 11);

  myStepperTelemetry.runPeriod = 150000; // 150ms

  myServo.setup(7);
}

void loop() {
  myBlinker13.loop();
  myBlinker12.loop();
  myButton.loop();
  mqtt.loop();
  myA0.loop();
  myBeeper.loop();
  myStepper.loop();
  myStepperTelemetry.loop();
  myServo.loop();
}
