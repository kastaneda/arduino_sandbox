#include <stdio.h>

// mqtt_hub.h

#define MQTT_MessageBufferSize 64

struct TopicSubscription {
  const char *topic;
  void (*onMessage)(char *payload);
};

struct TopicSubscription *MQTT_subscriptions = NULL;
int MQTT_subscriptionsCount = 0;

char MQTT_messageBuffer[MQTT_MessageBufferSize];
int MQTT_messageBufferCount = 0;

void MQTT_handleInboundChar(char incomingChar);
void MQTT_handleInboundLine();
void MQTT_handleInboundLine();

// mqtt_hub.c

void MQTT_handleInboundChar(char incomingChar) {
  if (incomingChar == '\n' || incomingChar == '\r') {
    if (MQTT_messageBufferCount) {
      MQTT_messageBuffer[MQTT_messageBufferCount + 1] = 0;
      MQTT_handleInboundLine();
      MQTT_messageBufferCount = 0;
    }
  } else {
    if (MQTT_messageBufferCount < (MQTT_MessageBufferSize - 1))
      MQTT_messageBuffer[MQTT_messageBufferCount++] = incomingChar;
  }
}

void MQTT_handleInboundLine() {
  printf("debug: MQTT_handleInboundLine()\n");
  char chTopic, chBuffer;
  for (int i = 0; i < MQTT_subscriptionsCount; i++) {
    for (int j = 0; j < MQTT_MessageBufferSize; j++) {
      chTopic = MQTT_subscriptions[i].topic[j];
      chBuffer = MQTT_messageBuffer[j];
      if (chTopic == chBuffer) {
        //printf("debug: chTopic=%c equals chBuffer=%c\n", chTopic, chBuffer);
        continue;
      }
      //printf("debug: chTopic=%d NOT equals chBuffer=%d\n", chTopic, chBuffer);
      if ((chTopic == '\0') && (chBuffer == ' ')) {
        printf("debug: i=%d\n", i);
        MQTT_subscriptions[i].onMessage(MQTT_messageBuffer + j + 1);
        return;
      }
      j = MQTT_MessageBufferSize;
    }
  }
}

// app.c

void onLed12(char *payload) {
  if (payload[0] == '1') {
    printf("digitalWrite(12, HIGH);\n");
  } else {
    printf("digitalWrite(12, LOW);\n");
  }
}

void onLed13(char *payload) {
  if (payload[0] == '1') {
    printf("digitalWrite(13, HIGH);\n");
  } else {
    printf("digitalWrite(13, LOW);\n");
  }
}

struct TopicSubscription topics[] = {
  {
    "dev/board05/led12/set",
    onLed12
  },
  {
    "dev/board05/led13/set",
    onLed13
  }
};

char *testInput =
  "foo bar\n"
  "test\n\n\n\n"
  "dev/board05/led12/set 1\n"
  "dev/board05/led13/set 0\n";

int main() {
  MQTT_subscriptions = topics;
  MQTT_subscriptionsCount = sizeof(topics) / sizeof(topics[0]);

  for (int i = 0; testInput[i]; i++) {
    printf("%c", testInput[i]);
    MQTT_handleInboundChar(testInput[i]);
  }

  return 0;
}
