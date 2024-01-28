#include "Arduino.h" 
#include "DebouncedToggleButton.h" 
#include "BlinkingLED.h" 

DebouncedToggleButton btn(2);
BlinkingLED led(LED_BUILTIN);

void setup() {
  btn.setup();
  led.setup();
}

void loop() {
  led.setBlinkEnabled(btn.getState()); // TODO FIXME
  btn.loop();
  led.loop();
}
