#ifndef __PRIORITY_QUEUE_H__
#define __PRIORITY_QUEUE_H__

#include "bheap.h"

typedef BHeap PriorityQueue;

/*
 * Crea una cola de prioridad vacia con las operaciones dadas
*/
PriorityQueue pqueue_create(unsigned initial_size, CompareFunction cmp,
                            CopyFunction copy, DestroyFunction destroy);

/*
 * Retorna 1 si la cola de prioridad esta vacia, 0 en caso contrario
*/
int pqueue_empty(PriorityQueue q);

/*
 * Retorna una copia del elemento maximo, osea el primero en la cola
*/
void* pqueue_max(PriorityQueue q);

/*
 * Remueve el elemento de maxima prioridad de la cola dejando una nueva
 * cola de prioridad
*/
void pqueue_remove_max(PriorityQueue q);

/*
 * Inserta una copia del dato en el lugar que le corresponde segun su prioridad
*/
void pqueue_insert(PriorityQueue q, void *data);

#endif /* __PRIORITY_QUEUE_H__ */