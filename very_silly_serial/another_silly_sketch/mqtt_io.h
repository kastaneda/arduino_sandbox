#ifndef MQTT_IO_H
#define MQTT_IO_H

#include <Arduino.h>
#include <Stream.h>

#include "loop_job.h"

#define MessageBufferSize 64

struct TopicSubscription {
  const char *topic;
  void (*onMessage)(char *payload);
};

class MessageHub: public ShouldLoop {
public:
  TopicSubscription *subscriptions = NULL;
  uint8_t subscriptionsCount = 0;

  void begin();
  void begin(Stream &s);
  void loopAt(unsigned long timeNow);

  //void send(char *topic, char *payload);
  //void send(char *topic, long *payload);

protected:
  Stream *io;

private:
  char messageBuffer[MessageBufferSize];
  uint8_t messageBufferCount = 0;

  void handleInboundChar(char incomingChar);
  void handleInboundLine();
};

/*
class MessageTelemetry: public MessageQuery, public ScheduledLoop {
public:
  unsigned long runPeriod = 250000; // default: 250ms
  unsigned long repeatUnchanged = 5000000; // default: 5s
  long (*readingSource)() = NULL;

protected:
  void runScheduled();

private:
  long lastReading = 0;
};
*/

#endif
