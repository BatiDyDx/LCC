#include <stdio.h>

int solve(float a, float b, float c, float d, float e, float f, float* x, float* y);

int main() {
  float x, y;
  printf("res: %d\n", solve(1, 1, 2, 3, 3, 0, &x, &y));
  printf("x: %f, y: %f\n", x, y);
  return 0;
}
