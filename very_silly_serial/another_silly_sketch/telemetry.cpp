#include "telemetry.h"

void TelemetryReporter::setup(MessageQueryHub *MQ1, const char *topic1, long runPeriod1) {
  this->MQ = MQ1;
  this->topic = topic1;
  this->runPeriod = runPeriod1;
}

void TelemetryReporter::runScheduled() {
  long reading;
  if (this->readingSource) {
    reading = this->readingSource();

    if (reading != this->lastReading) {
      this->MQ->send(this->topic, reading);
      this->lastReading = reading;
    }
  }
}
