#ifndef _CDLIST_H_
#define _CDLIST_H_ // Circular double linked list

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct _CDList{
    int data;
    struct _CDList* next;
    struct _CDList* prev;
} CDList;

CDList* cdlist_init(int arr[], size_t len);

int cdlist_empty(CDList* head);

size_t cdlist_len(CDList* head);

int cdlist_contains(CDList* head, int data);

int cdlist_index(CDList* head, int data);

CDList* cdlist_insert(CDList* head, size_t pos, int data);

CDList* cdlist_delete(CDList* head, size_t pos);

void cdlist_free(CDList* head);

void cdlist_print(CDList* head, size_t offset);

void cdlist_visit(CDList* head, void (*f)(int));

#endif