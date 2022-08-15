#ifndef _DLIST_H_
#define _DLIST_H_ // Double linked list

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct _DNode {
    int data;
    struct _DNode* prev;
    struct _DNode* next;
} DNode;

typedef struct {
    DNode *first, *last;
} DList;

typedef enum {
    DLIST_FORWARD,
    DLIST_BACKWARD
} DLIST_VISIT_DIR;

DList* dlist_init(int arr[], size_t len);

int dlist_empty(DList* list);

void dlist_append_start(DList* list, int data);

void dlist_append_last(DList* list, int data);

size_t dlist_len(DList* list);

int dlist_insert(DList* list, size_t pos, int data);

int dlist_delete(DList* list, size_t pos);

int dlist_contains(DList* list, int data);

int dlist_index(DList* list, int data);

void dlist_free(DList* list);

void dlist_visit(DList* list, void (*f)(int), DLIST_VISIT_DIR order);

void dlist_print(DList* list);

#endif