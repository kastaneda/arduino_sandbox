#include "Arduino.h" 

class PeriodicJob {
public:
  virtual void setup() = 0;
  virtual void loopWhen(unsigned long timeNowMicros) = 0;

  void loop() {
    this->loopWhen(micros());
  }
};

class ScheduledJob: public PeriodicJob {
public:
  unsigned long lastRunMicros;
  unsigned long delayDurationMicros;

  void loopWhen(unsigned long timeNowMicros) {
    unsigned long timeSinceLastRun;
    timeSinceLastRun = timeNowMicros - this->lastRunMicros;
    
    if (timeSinceLastRun >= this->delayDurationMicros) {
      this->loopScheduled();
      this->lastRunMicros = timeNowMicros;
    }
  }

  void setDelayDuration(unsigned long durationMicros) {
    if (this->delayDurationMicros == durationMicros) {
      return;
    }

    this->delayDurationMicros = durationMicros;
    this->lastRunMicros = micros();
  }

protected:
  virtual void loopScheduled() = 0;
};

class DebouncedToggleButton: public PeriodicJob {
public:
  DebouncedToggleButton(int pin) {
    this->buttonPin = pin;
    this->toggleState = true;       // turned on by default
    this->buttonState = HIGH;       // HIGH == not pressed (pull-up)
    this->lastButtonState = HIGH;
    this->debounceDelay = 50000;    // 50 ms
    this->lastDebounceTime = micros();
  }

  bool getState() {
    return this->toggleState;
  }

  void setup() {
    pinMode(this->buttonPin, INPUT_PULLUP);
  }

  void loopWhen(unsigned long timeNowMicros) {
    int reading = digitalRead(this->buttonPin);

    if (reading != this->lastButtonState) {
      this->lastDebounceTime = timeNowMicros;
    }

    if ((timeNowMicros - this->lastDebounceTime) > this->debounceDelay) {
      if (reading != this->buttonState) {
        this->buttonState = reading;
        if (this->buttonState == HIGH) {
          this->toggleState = ! this->toggleState;
          // TODO: maybe call some onclick pointer function?
        }
      }
    }

    this->lastButtonState = reading;
  }

private:
  bool toggleState;
  int buttonPin;
  int buttonState;
  int lastButtonState;
  unsigned long lastDebounceTime;
  unsigned long debounceDelay;
};

class BlinkingLED: public ScheduledJob {
public:
  BlinkingLED(int pin) {
    this->ledPin = pin;
    this->ledState = false;
    this->blinkEnabled = true;
    this->delayDurationMicros = 500000;
    this->lastRunMicros = micros();
  }

  void setBlinkEnabled(bool enabled) {
    this->blinkEnabled = enabled;
  }

  void setup() {
    pinMode(this->ledPin, OUTPUT);
  }

  void loopScheduled() {
    this->ledState = ! this->ledState;
    digitalWrite(this->ledPin, (this->blinkEnabled && this->ledState) ? HIGH : LOW);
  }

private:
  int ledPin;
  bool blinkEnabled;
  bool ledState;
};

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
