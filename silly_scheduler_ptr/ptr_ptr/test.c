#include <stdio.h>

typedef void* (*recursion_t)();

recursion_t turn_LED_on();
recursion_t turn_LED_off();

recursion_t turn_LED_on() {
  printf("digitalWrite(LED_BUILTIN, HIGH);");
  return *turn_LED_off;
}

recursion_t turn_LED_off() {
  static int count = 5;
  printf("digitalWrite(LED_BUILTIN, LOW);");
  return (--count) ? *turn_LED_on : NULL;
}

int main() {
  recursion_t step = turn_LED_on;

  for (int t = 0; t < 15; t++) {
    printf("t=%02d: ", t);
    if (step) {
      step = step();
    } else {
      printf("(null)");
    }
    printf("\n");
  }

  return 0;
}
