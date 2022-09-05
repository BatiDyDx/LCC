#include <stdio.h>
#include <assert.h>

// Ejercicio 1
void ex1() {
  assert(0b10000000000000000000000000000000 == 1 << 31);
  assert(0b10000000000000001000000000000000 == ((1 << 31) | (1 << 15)));
  assert(0b11111111111111111111111100000000 == (-1 & -256));
  assert(0b10101010000000000000000010101010 == (0xAA | (0xAA << 24)));
  assert(0b00000000000000000000010100000000 == 5 << 8);
  assert(0b11111111111111111111111011111111 == ( -1 & ( ~(1 << 8) ) ));
  assert(0b11111111111111111111111111111111 == 0 - 1);
  assert(0b00000000000000000000000000000000 == 0x80000000 + 0x80000000);
}

int is_one(long n, int b) {
  return (n >> b) & 1;
}

void printbin(unsigned long n) {
  for (int i = sizeof(unsigned long) * 8; i > 0; i--)
  	putchar(is_one(n, i - 1) ? '1': '0');
  putchar('\n');
}

// Ejercicio 4
void swap3(int *a, int *b, int *c) {
 // a -> b, b -> c, c -> a
 *a = *a ^ *b; // a = a^b
 *b = *a ^ *b; // b = (a^b)^b == a
 *a = *a ^ *b; // a = (a^b)^a == b
 *a = *a ^ *c; // a = b^c
 *c = *a ^ *c; // c = (b^c)^c == b
 *a = *a ^ *c; // a = (b^c)^b == c
}

// Ejercicio 5
void encode_xor() {
  char msg[30];
  int code;
  printf("Inserte el mensaje a codificar: ");
  scanf("%s", msg);
  printf("Inserte el codigo para la codificacion: ");
  scanf("%d", &code);
  printf("Mensaje codificado: \n");
  int i = 0;
  while (msg[i])
    putchar(msg[i++] ^ code);
}

// Ejercicio 6
unsigned mult(unsigned a, unsigned b) {
  unsigned res;
  if (b == 0)
  	res = 0;
  else if (b == 1)
  	res = a;
  else
    res = mult(a << 1, b >> 1) + (b % 2 == 0 ? 0 : a);
  return res;
}

// Ejercicio 7
typedef struct {
  unsigned short n[16]; // sizeof(short) * 16 = 2 bytes * 16 = 256 bits
} uint_256bits;

// a)

int main() {
  ex1();
  printf("N: %d, N + N: %d\n", 0x80000000, 0x80000000 + 0x80000000);
  return 0;
}
