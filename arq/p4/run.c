#include <assert.h>

unsigned int campesino_ruso(unsigned int i, unsigned int j);
int det22(int a, int b, int c, int d);
unsigned exp(unsigned char i); // 2 ** i

int main() {
  assert(campesino_ruso(4, 5) == 20);
  assert(exp(31) == 2 << 31);
  assert(det22(4, 2, 3, 8) == 26);
  return 0;
}

