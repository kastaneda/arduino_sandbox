#ifndef MQTT_IO_H
#define MQTT_IO_H

#include <Arduino.h>
#include <Stream.h>

#include "loop_job.h"

#define MessageBufferSize 64

class MessageQuery {
public:
  void begin();
  void begin(Stream &s);

protected:
  Stream *io;
};

/*
struct TopicSubscription {
  const char *topic;
  void (*onMessage)(char *payload) = 0;
};
*/

class MessageReader: public MessageQuery, public ShouldLoop {
public:
  // TopicSubscription *subscriptions;
  void (*FIXME_testCommand)() = 0;

  void loopAt(unsigned long timeNow);

private:
  char messageBuffer[MessageBufferSize];
  unsigned int messageBufferCount = 0;
  void FIXME_handleCommand();
};

/*
class MessageTelemetry: public MessageQuery, public ScheduledLoop {
public:
  unsigned long runPeriod = 250000; // default: 250ms
  unsigned long repeatUnchanged = 5000000; // default: 5s
  long (*readingSource)() = 0;

protected:
  void runScheduled();

private:
  long lastReading = 0;
};
*/

#endif
