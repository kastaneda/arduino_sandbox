#include "Arduino.h" 
#include "DebouncedToggleButton.h" 
#include "BlinkingLED.h" 
#include "SillyStepper.h"
#include "DebugLogger.h"

DebouncedToggleButton btn(2);
BlinkingLED led(LED_BUILTIN);
SillyStepper motor(8, 9, 10, 11);
DebugLogger dbg(0);

void setup() {
  btn.setup();
  led.setup();
  motor.setup();
  dbg.setup();
  dbg.setDelayDuration(250000);
  pinMode(A0, INPUT);
  analogReference(INTERNAL);
}

void loop() {
  int potReading;

  potReading = analogRead(A0);
  potReading = potReading >> 4 << 4;
  dbg.setValue(potReading);

  // TODO FIXME what's wrong with that potentiometer?
  motor.setTargetStep(potReading);

  led.setBlinkEnabled(btn.getState()); // TODO FIXME

  btn.loop();
  led.loop();
  motor.loop();
  dbg.loop();
}
