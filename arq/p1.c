#include <stdio.h>
#include <assert.h>

// Ejercicio 1
void ex1() {
  assert(0b10000000000000000000000000000000 == 1 << 31);
  assert(0b10000000000000001000000000000000 == ((1 << 31) | (1 << 15)));
  assert(0b11111111111111111111111100000000 == (-1 & -256));
  assert(0b10101010000000000000000010101010 == (0xAA | (0xAA << 24)));
  assert(0b00000000000000000000010100000000 == 5 << 8);
  assert(0b11111111111111111111111011111111 == (-1 & (~(1 << 8))));
  assert(0b11111111111111111111111111111111 == 0 - 1);
  assert(0b00000000000000000000000000000000 == 0x80000000 + 0x80000000);
}

// Ejercicio 2
int is_one(long n, int b) {
  return (n >> b) & 1;
}

// Ejercicio 3 
void printbin(unsigned long n) {
  for (int i = sizeof(unsigned long) * 8; i > 0; i--)
    putchar(is_one(n, i - 1) ? '1' : '0');
  putchar('\n');
}

// Ejercicio 4
void swap3(int *a, int *b, int *c) {
 // a -> b, b -> c, c -> a
 *a = *a ^ *b ^ *c;
 *b = *a ^ *b ^ *c; // b = ( a ^ b ^ c ) ^ b ^ c == a
 *c = *a ^ *b ^ *c; // c = ( a ^ b ^ c ) ^ a ^ c == b
 *a = *a ^ *b ^ *c; // a = ( a ^ b ^ c ) ^ a ^ b == c
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

//Ejercicio 6
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
  unsigned short n[16]; //sizeof(short) * 16 = 2 bytes * 16 = 256 bits
} uint_256bits;

// a)
int is_zero_256b(uint_256bits x) {
  for (int i = 0; i < 16; i++)
    if (x.n[i])
      return 0;
  return 1;
}

int is_one_256b(uint_256bits x) {
  int flag = 0;
  for (int i = 16; i > 1 && !flag; --i)
    if (x.n[i])
      flag = 1;
  return !flag && (x.n[0] == 1);
}

int is_even_256b(uint_256bits x) {
  return x.n[0] & 0;
}

uint_256bits lshift(uint_256bits x, int n) {
  uint_256bits y;

  int block_size = sizeof(short) * 8;
  int offset = n / block_size;
  int nmod = n % block_size;

  for (int i = 15; i >= 0; --i) {
    if (i - offset < 0) {
      y.n[i] = 0;
      continue;
    }
    y.n[i] = (x.n[i - offset] << nmod);
    if (i - offset - 1 >= 0)
      y.n[i] = y.n[i] | x.n[i - offset - 1] >> (block_size - nmod);
  }
  return y;
}

uint_256bits rshift(uint_256bits x, int n) {
  uint_256bits y;

  int block_size = sizeof(short) * 8;
  int offset = n / block_size;
  int nmod = n % block_size;

  for (int i = 0; i < 16; ++i) {
    if (i + offset >= 16) {
      y.n[i] = 0;
      continue;
    }
    y.n[i] = (x.n[i + offset] >> nmod);
    if (i + offset + 1 <= 15)
      y.n[i] = y.n[i] | x.n[i + offset + 1] << (block_size - nmod);
  }

  return y;
}

uint_256bits add_256b(uint_256bits x, uint_256bits y) {
  int carry = 0, tmp;
  uint_256bits z;
  for (int i = 0; i < 16; ++i) {
    tmp = (unsigned)x.n[i] + (unsigned)y.n[i] + carry;
    z.n[i] = (unsigned short)tmp;
    carry = (tmp >> 16) & 1;
  }

  return z;
}

//Ejercicio 8
uint_256bits mult_256b(uint_256bits x, uint_256bits y) {
  int stop = 0;
  uint_256bits z;

  if (is_zero_256b(y))
    for (int i = 0; i < 16; z.n[i++] = 0);
  else if (is_one_256b(y)) {
    for (int i = 0; i < 16; z.n[i] = x.n[i], i++);
  }
  else {
    z = mult_256b(lshift(x, 1), rshift(y, 1));
    if (!is_even_256b(y))
      z = add_256b(z, x);
  }
  return z;
}

//Ejercicio 9
#define MANT_F(X) (*( (int*) (&X) ) & 0x007FFFFF) // Mantisa para float
#define EXP_F(X) ((*( (int*) (&X)) >> 23) & 0x000000FF) // Exponente para float

// Ejercicio 10
// d)
int myisnan(float f) {
  return EXP_F(f) == 0xFF && MANT_F(f) != 0;
}

// f)
int myisinf(float f) {
  return EXP_F(f) == 0xFF && MANT_F(f) == 0;
}

void test_uint256bits() {
  uint_256bits    x, y, z;
  x.n[0] = 0xFFFF;
  y.n[0] = 0x0001;
  z = add_256b(x, y);
  assert(z.n[0] == 0 && z.n[1] == 1);
}

int main() {
  ex1();
  test_uint256bits();
  assert(myisinf(1.0 / 0.0));
  assert(myisinf(-1.0 / 0.0));
  assert(myisnan(0.0 / 0.0));
  return 0;
}
