#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define NPUNTOS 100000
#define NTHREADS 100
#define RADIO 1000

int puntos_circ = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

static inline int square(int n) {return n * n;}

void* montecarlo(void* _arg) {
  int x, y;
  for (int i = 0; i < NPUNTOS / NTHREADS; i++) {
    x = rand() % (2 * RADIO);
    y = rand() % (2 * RADIO);
    if (square(x - RADIO) + square(y - RADIO) <= square(RADIO)) {
      pthread_mutex_lock(&mutex);
      puntos_circ++;
      pthread_mutex_unlock(&mutex);
    }
  }
  return NULL;
}

int main() {
  srand(time(NULL));
  pthread_t threads[NTHREADS];
  pthread_mutex_init(&mutex, NULL);
  for (int i = 0; i < NTHREADS; i++)
    pthread_create(threads + i, NULL, montecarlo, NULL);

  for (int i = 0; i < NTHREADS; i++)
    pthread_join(threads[i], NULL);

  printf("%lf\n", 4 * (double) puntos_circ / NPUNTOS);
  return 0;
}

