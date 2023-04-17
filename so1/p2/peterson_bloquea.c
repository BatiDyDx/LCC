#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>

#define NVISITANTES 1000000

int flag[2] = {0, 0};
int turno = 0;

int visitantes = 0;

static inline void incl(int *p) {
  asm("lock; incl %0" : "+m"(*p) : : "memory");
  //(*p)++;
}

void* molinete0(void* _arg) {
  for (int i = 0; i < NVISITANTES; i++){
    flag[0] = 1;
    turno = 1;
    //asm("mfence");
    while (flag[1] == 1 && turno == 1){}
    //visitantes++;
    incl(&visitantes);
    flag[0] = 0;
  }
    //printf("m0 \n");
}

void* molinete1(void* _arg) {
  for (int i = 0; i < NVISITANTES; i++){
    flag[1] = 1;
    turno = 0;
    //asm("mfence");    
    while (flag[0] == 1 && turno == 0){}
    //visitantes++;
    incl(&visitantes);
    flag[1] = 0;
  }
    //printf("m1 \n");
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