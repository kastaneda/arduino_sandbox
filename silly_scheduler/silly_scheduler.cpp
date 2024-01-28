#include "Arduino.h" 
#include "DebouncedToggleButton.h" 
#include "BlinkingLED.h" 
#include "SillyStepper.h"

DebouncedToggleButton btn(2);
BlinkingLED led(LED_BUILTIN);
SillyStepper motor(8, 9, 10, 11);

void setup() {
  btn.setup();
  led.setup();
  motor.setup();
}

void loop() {
  led.setBlinkEnabled(btn.getState()); // TODO FIXME

  // TODO FIXME what's wrong with that potentiometer?
  motor.setTargetStep(analogRead(A0) >> 5 << 5);

  btn.loop();
  led.loop();
  motor.loop();
}
