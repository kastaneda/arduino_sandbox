#ifndef MESSAGE_QUERY_H
#define MESSAGE_QUERY_H

#include <Arduino.h>
#include <Stream.h>

#include "void_loop.h"

#define MessageQueryBufferSize 64

struct MessageQuerySubscription {
  const char *topic;
  void (*onMessage)(char *payload);
};

class MessageQueryHub: public VoidLoop {
public:
  MessageQuerySubscription *subscriptions = NULL;
  uint8_t subscriptionsCount = 0;
  char *payload = 0;

  void begin();
  void begin(Stream &s);
  void loopAt(unsigned long timeNow);

  long parseInt();
  bool parseBool();
  void send(const char *topic, char *payload);
  void send(const char *topic, long payload);

protected:
  Stream *io;

private:
  char messageBuffer[MessageQueryBufferSize];
  uint8_t messageBufferCount = 0;

  void handleInboundChar(char incomingChar);
  void handleInboundLine();
};

// TODO: send / sendNow, output message buffer
// if (Serial.availableForWrite() > msgSize) { ... }

#define MessageQuerySubscribe(Hub, Topics) \
    Hub.subscriptions = Topics; \
    Hub.subscriptionsCount = sizeof(Topics) / sizeof(Topics[0]);

#endif
