#include <assert.h>
#include <stdio.h>

unsigned int campesino_ruso(unsigned int i, unsigned int j);
float det22(float a, float b, float c, float d);

int main() {
  assert(campesino_ruso(4, 5) == 20);
  return 0;
}

