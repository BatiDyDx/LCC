#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>

#define NVISITANTES 10000000

int flag[2] = {0, 0};
int turno = 0;

int visitantes = 0;

void* molinete0(void* _arg) {
  for (int i = 0; i < NVISITANTES; i++){
    turno = 1;
    flag[0] = 1;

    asm("mfence");
    while (flag[1] == 1 && turno == 1);
    visitantes++;
    flag[0] = 0;
    asm("mfence");
  }
  return NULL;
}

void* molinete1(void* _arg) {
  for (int i = 0; i < NVISITANTES; i++){
    turno = 0;
    flag[1] = 1;
    
    asm("mfence");
    while (flag[0] == 1 && turno == 0);
    visitantes++;
    flag[1] = 0;
    asm("mfence");
  }
  return NULL;
}

int main() {
    pthread_t t0, t1;
    pthread_create(&t0, NULL, molinete0, NULL);
    pthread_create(&t1, NULL, molinete1, NULL);
    
    pthread_join(t0, NULL);
    pthread_join(t1, NULL);

    printf("Visitantes: %d\n", visitantes);

    return 0;
}
