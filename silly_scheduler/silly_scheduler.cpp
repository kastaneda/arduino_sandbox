#include "Arduino.h" 
#include "DebouncedToggleButton.h" 
#include "BlinkingLED.h" 
#include "SillyStepper.h"
#include "AnalogAverage.h"
#include "DebugLogger.h"

DebouncedToggleButton btn(2);
BlinkingLED led(LED_BUILTIN);
SillyStepper motor(8, 9, 10, 11);
AnalogAverage pot(A0);
DebugLogger dbg(0);

void setup() {
  btn.setup();
  led.setup();
  motor.setup();
  pot.setup();
  dbg.setup();
  dbg.setDelayDuration(250000);
  analogReference(INTERNAL);
}

void loop() {
  btn.loop();
  led.loop();
  motor.loop();
  pot.setup();
  dbg.loop();

  dbg.setValue(pot.getValue());
  motor.setTargetStep(pot.getValue());
  led.setBlinkEnabled(btn.getState());
}
