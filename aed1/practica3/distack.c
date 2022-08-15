#include "distack.h"

DIStack distack_init(size_t size) {
    DIStack s = malloc(sizeof struct _DIStack);
    assert(s != NULL);
    s->arr = create(size);
    s->last = 0;
    return s;
}

void distack_free(DIStack s) {
    destroy(s->arr);
    free(s);
}

int distack_empty(DIStack s) { return s->last == -1; }

int distack_top(DIStack s) {
    assert(!distack_empty(s));
    return s->arr[s->last];
}

void distack_push(DIStack s, int data) {
    if (s->last + 1 == s->arr->size)
        resize(s->arr, (s->arr->size *= 2));
    s->arr[++s->last] = data;
}

void distack_pop(DIStack s) {
    if (distack_empty(s))
        return ;
    s->last -= 1;
}

void distack_print(DIStack s) {
    putchar('[');
    for (int i = 0; i <= s->last; i++)
        printf("%d, ", s->arr[i]);
    putchar(']');
    putchar('\n');
}