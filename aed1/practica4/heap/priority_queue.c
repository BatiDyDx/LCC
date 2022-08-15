#include "priority_queue.h"
#include <stdlib.h>
#include <assert.h>

PriorityQueue pqueue_create(unsigned initial_size, CompareFunction cmp,
                            CopyFunction copy, DestroyFunction detroy) {
  return bheap_init(initial_size, cmp, copy, detroy);
}

int pqueue_empty(PriorityQueue q) {
  return bheap_empty(q);
}

void* pqueue_max(PriorityQueue q) {
  if (pqueue_empty(q))
    return NULL;
  return q->copy(q->arr[0]);
}

void pqueue_remove_max(PriorityQueue q) {
  q->destroy(bheap_remove_max(q));
}

void pqueue_insert(PriorityQueue q, void *data) {
  bheap_insert(q, q->copy(data));
}
