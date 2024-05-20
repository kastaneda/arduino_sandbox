#include "telemetry.h"

void TelemetryReporter::setup(MessageQueryHub *MQ, const char *topic, long runPeriod) {
  this->MQ = MQ;
  this->topic = topic;
  this->runPeriod = runPeriod;
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
