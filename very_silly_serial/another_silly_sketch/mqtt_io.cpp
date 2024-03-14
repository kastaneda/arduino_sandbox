#include "mqtt_io.h"

void MessageQuery::begin() {
  this->begin(Serial);
}

void MessageQuery::begin(Stream &s) {
  this->io = &s;
}

void MessageReader::loopAt(unsigned long timeNow) {
  if (this->io->available() > 0) {
    char incomingChar = this->io->read();

    if (this->messageBufferCount < (MessageBufferSize - 1)) {
      this->messageBuffer[this->messageBufferCount++] = incomingChar;
    }

    if (incomingChar == '\n' || incomingChar == '\r') {
      this->messageBuffer[this->messageBufferCount + 1] = 0;
      this->FIXME_handleCommand();
      this->messageBufferCount = 0;
    }
  }
}

void MessageReader::FIXME_handleCommand() {
  this->io->write("FIXME_testCommand()\n");
  if (this->FIXME_testCommand) this->FIXME_testCommand();
}
