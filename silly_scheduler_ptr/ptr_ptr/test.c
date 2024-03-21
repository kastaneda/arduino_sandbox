#include <stdio.h>

struct fn_sequence {
  // scheduling infomration?
  // delay before specific step?
  struct fn_sequence* (*func)();
};

struct fn_sequence* turn_LED_on();
struct fn_sequence* turn_LED_off();

struct fn_sequence endless_blinking_led[2] = {
  { turn_LED_on },
  { turn_LED_off }
};

struct fn_sequence* turn_LED_on() {
  printf("digitalWrite(LED_BUILTIN, HIGH);");
  return &endless_blinking_led[1];
}

struct fn_sequence* turn_LED_off() {
  static int count = 5;
  printf("digitalWrite(LED_BUILTIN, LOW);");
  return (--count) ? &endless_blinking_led[0] : NULL;
}

int main() {
  struct fn_sequence* seq_step = &endless_blinking_led[0];

  for (int t = 0; t < 15; t++) {
    printf("t=%02d: ", t);
    if (seq_step) {
      seq_step = seq_step->func();
    } else {
      printf("(null)");
    }
    printf("\n");
  }

  return 0;
}
