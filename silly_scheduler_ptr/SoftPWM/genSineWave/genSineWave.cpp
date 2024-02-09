#include <stdio.h>
#include <math.h>

const int stepsTotal = 256;
const int stepsPerRow = 16;
const int sineResulution = 255;

int main ()
{
  double sineArg, sineValue;
  int intValue;
  printf("const PROGMEM uint8_t SineWave[] = {");
  for (int step = 0; step < stepsTotal; step++) {
    if ((step % stepsPerRow) == 0) printf("\n ");
    sineArg = step * M_PI_2 / stepsTotal;
    sineValue = sin(sineArg);
    intValue = (int) floor(sineResulution * sineValue + .5);
    printf(" %d", intValue);
    if ((stepsTotal - step) > 1) printf(",");
  }
  printf("\n};\n");
  return 0;
}
