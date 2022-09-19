#include <stdio.h>

unsigned long fact_iter(unsigned long);
unsigned long fact_rec(unsigned long);

int main() {
  unsigned long x;
  scanf("%lu", &x);
  printf("Factorial iterativo: %lu\n", fact_iter(x));
  printf("Factorial recursivo: %lu\n", fact_rec(x));
  return 0;
}
