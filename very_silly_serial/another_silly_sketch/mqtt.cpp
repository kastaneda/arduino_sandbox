#include "mqtt.h"

void MessageQueryHub::begin() {
  this->begin(Serial);
}

void MessageQueryHub::begin(Stream &s) {
  this->io = &s;
}

void MessageQueryHub::loopAt(unsigned long timeNow) {
  if (this->io->available())
    this->handleInboundChar(this->io->read());
}

void MessageQueryHub::handleInboundChar(char incomingChar) {
  if (this->messageBufferCount < (MessageQueryBufferSize - 1))
    this->messageBuffer[this->messageBufferCount++] = incomingChar;

  if (incomingChar == '\n' || incomingChar == '\r') {
    this->messageBuffer[this->messageBufferCount + 1] = 0;
    this->handleInboundLine();
    this->messageBufferCount = 0;
  }
}

void MessageQueryHub::handleInboundLine() {
  char chTopic, chBuffer;
  for (uint8_t i = 0; i < this->subscriptionsCount; i++) {
    for (uint8_t j = 0; j < MessageQueryBufferSize; j++) {
      chTopic = this->subscriptions[i].topic[j];
      chBuffer = this->messageBuffer[j];
      if (chTopic == chBuffer) continue;
      if ((chTopic == '\0') && (chBuffer == ' ')) {
        this->subscriptions[i].onMessage(this->messageBuffer + j + 1);
        return;
      }
      j = MessageQueryBufferSize;
    }
  }
}

long MessageQueryHub::parseInt() {
  long result = 0;
  uint8_t sign = 1;
  uint8_t i = 0;
  if (this->payload[i] == '-') {
    sign = -1;
    i++;
  }
  while (this->payload[i]) {
    if ((this->payload[i] >= '0') && (this->payload[i] <= '9'))
      result = result * 10 + (this->payload[i] - '0');
    i++;
  }
  return sign * result;
}

bool MessageQueryHub::parseBool() {
  return (bool) this->parseInt();
}

void MessageQueryHub::send(char *topic, char *payload) {
  this->io->print(topic);
  this->io->print(' ');
  this->io->println(payload);
}

void MessageQueryHub::send(char *topic, long payload) {
  this->io->print(topic);
  this->io->print(' ');
  this->io->println(payload);
}
