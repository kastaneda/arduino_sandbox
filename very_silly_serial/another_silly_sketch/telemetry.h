#ifndef TELEMETRY_H
#define TELEMETRY_H

#include <Arduino.h>

#include "void_loop.h"
#include "mqtt.h"

class TelemetryReporter: public ScheduledLoop {
public:
  MessageQueryHub *MQ;
  const char *topic;
  long (*readingSource)() = NULL;

  void setup(MessageQueryHub *MQ1, const char *topic1, long runPeriod1);

protected:
  long lastReading = 0;
  void runScheduled();
};

// TODO: force repeat after N unchanged readings

#endif
