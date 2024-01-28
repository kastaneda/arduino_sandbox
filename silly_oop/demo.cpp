#include <iostream>

class PeriodicJob {
public:
  virtual void loop(uint8_t timeNow) = 0;
};

class ScheduledJob: public PeriodicJob {
public:
  uint8_t lastRun;
  uint8_t delayDuration;

  void loop(uint8_t timeNow) {
    uint8_t timeSinceLastRun;
    timeSinceLastRun = timeNow - this->lastRun;
    
    // debug
    std::cout << "Time now: " << (int) timeNow
      << ", last run: " << (int) this->lastRun
      << ", time since last run: " << (int) timeSinceLastRun << "\n";

    if (timeSinceLastRun >= this->delayDuration) {
      this->loopScheduled();
      this->lastRun = timeNow;
    }
  }

protected:
  virtual void loopScheduled() = 0;
};

class DebouncedPushButton: public ScheduledJob {
protected:
  virtual void loopScheduled() {
    std::cout << "It's now!\n";
  }
};

int main() {
  DebouncedPushButton btn;
  btn.lastRun = 0;
  btn.delayDuration = 10;

  for (int i = 0; i <= 300; i++) {
    btn.loop(i);
  }

  return 0;
}
