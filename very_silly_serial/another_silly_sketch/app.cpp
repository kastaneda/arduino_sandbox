#include <Arduino.h>

#include "void_loop.h"
#include "mqtt.h"
#include "telemetry.h"
#include "debouncer.h"
#include "blinking_led.h"
#include "beeper.h"
#include "servo_loop.h"
#include "stepper_loop.h"

MessageQueryHub MQTT;
BlinkingLED myBlinker12, myBlinker13;
const uint8_t myButtonPin = 2;
Debouncer myButton;
Beeper myBeeper;
StepperLoop myStepper;
ServoLoop myServo;
TelemetryReporter myA0, myStepperTelemetry;

MessageQuerySubscription myTopics[] = {
  {
    "dev/board05/led12/set",
    [](char *payload) {
      bool newState = MQTT.parseBool();
      if (myBlinker12.enabled != newState) myBeeper.beep();
      myBlinker12.enabled = newState;
    }
  },
  {
    "dev/board05/led13/set",
    [](char *payload) {
      bool newState = MQTT.parseBool();
      if (myBlinker13.enabled != newState) myBeeper.beep();
      myBlinker13.enabled = newState;
    }
  },
  {
    "dev/board05/stepper/set",
    [](char *payload) {
      myStepper.setTargetStep(MQTT.parseInt());
      myBeeper.beep(10000);
    }
  },
  {
    "dev/board05/beeper/set",
    [](char *payload) {
      myBeeper.beep(MQTT.parseInt());
    }
  },
  {
    "dev/board05/servo/set",
    [](char *payload) {
      myServo.write(MQTT.parseInt());
    }
  }
};

void setup() {
  Serial.begin(9600);

  MQTT.begin();
  MessageQuerySubscribe(MQTT, myTopics);

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
    MQTT.send("dev/board05/led12", (long) (myBlinker12.enabled ? 1 : 0));
  };

  pinMode(A0, INPUT);
  //analogReference(INTERNAL); // on USB it makes only worse
  myA0.setup(&MQTT, "dev/board05/A0", 400000);
  myA0.readingSource = []() {
    return (long) analogRead(A0);
  };

  myBeeper.setup(5);

  myStepper.setup(8, 9, 10, 11);

  myStepperTelemetry.setup(&MQTT, "dev/board05/stepper", 150000);
  myStepperTelemetry.readingSource = []() {
    return myStepper.getCurrentStep();
  };

  myServo.setup(7);
}

void loop() {
  MQTT.loop();
  myBlinker13.loop();
  myBlinker12.loop();
  myButton.loop();
  myA0.loop();
  myBeeper.loop();
  myStepper.loop();
  myStepperTelemetry.loop();
  myServo.loop();
}
