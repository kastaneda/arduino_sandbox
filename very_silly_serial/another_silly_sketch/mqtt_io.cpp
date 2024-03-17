#include "mqtt_io.h"

void MessageHub::begin() {
  this->begin(Serial);
}

void MessageHub::begin(Stream &s) {
  this->io = &s;
}

void MessageHub::loopAt(unsigned long timeNow) {
  if (this->io->available())
    this->handleInboundChar(this->io->read());
}

void MessageHub::handleInboundChar(char incomingChar) {
  if (this->messageBufferCount < (MessageBufferSize - 1))
    this->messageBuffer[this->messageBufferCount++] = incomingChar;

  if (incomingChar == '\n' || incomingChar == '\r') {
    this->messageBuffer[this->messageBufferCount + 1] = 0;
    this->handleInboundLine();
    this->messageBufferCount = 0;
  }
}

void MessageHub::handleInboundLine() {
  char chTopic, chBuffer;
  for (uint8_t i = 0; i < this->subscriptionsCount; i++) {
    for (uint8_t j = 0; j < MessageBufferSize; j++) {
      chTopic = this->subscriptions[i].topic[j];
      chBuffer = this->messageBuffer[j];
      if (chTopic == chBuffer) continue;
      if ((chTopic == '\0') && (chBuffer == ' ')) {
        this->subscriptions[i].onMessage(this->messageBuffer + j + 1);
        return;
      }
    }
  }
}

void MessageHub::send(char *topic, char *payload) {
  this->io->print(topic);
  this->io->print(' ');
  this->io->println(payload);
}

void MessageHub::send(char *topic, long payload) {
  this->io->print(topic);
  this->io->print(' ');
  this->io->println(payload);
}
