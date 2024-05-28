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
  if (this->messageBufferCount < (MessageQueryBufferSize - 2))
    if (incomingChar >= 32)
      this->messageBuffer[this->messageBufferCount++] = incomingChar;

  if (incomingChar == '\n' || incomingChar == '\r') {
    this->messageBuffer[this->messageBufferCount] = 0;
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
        this->payload = this->messageBuffer + j + 1;
        this->subscriptions[i].onMessage(this->payload);
        return;
      }
      break;
    }
  }
}

long MessageQueryHub::parseInt() {
  long result = 0;
  uint8_t sign = 1;
  uint8_t i = 0;
  if (this->payload[i] == '+') i++;
  else if (this->payload[i] == '-') {
    sign = -1;
    i++;
  }
  while (this->payload[i]) {
    this->io->print(this->payload[i], HEX);
    this->io->print('\n');
    if ((this->payload[i] >= '0') && (this->payload[i] <= '9')) {
      result = result * 10 + (this->payload[i] - '0');
      i++;
    } else break;
  }
  return sign * result;
}

bool MessageQueryHub::parseBool() {
  // TODO: 'true', 'false', 'on', 'off'
  return (bool) this->parseInt();
}

void MessageQueryHub::send(const char *topic, char *payload) {
  this->io->print(topic);
  this->io->print(' ');
  this->io->println(payload);
}

void MessageQueryHub::send(const char *topic, long payload) {
  this->io->print(topic);
  this->io->print(' ');
  this->io->println(payload);
}
