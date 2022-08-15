#ifndef _SLIST_H_
#define _SLIST_H_ // Simple linked list

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct _SNode {
    int data;
    struct _SNode *next;
} SNode;

typedef struct {
    SNode* first;
    SNode* last;
} SList;


SNode* snode_init(int arr[], size_t len);

int snode_empty(SNode* list);

SNode* snode_append_start(SNode* list, int data);

SNode* snode_remove_start(SNode* list);

SNode* snode_append_end(SNode* list, int data);

size_t snode_len(SNode* list);

SNode* snode_link(SNode* list1, SNode* list2);

SNode* snode_insert(SNode* list, size_t pos, int data);

SNode* snode_delete(SNode* list, size_t pos);

int snode_contains(SNode* list, int data);

int snode_index(SNode* list, int data);

SNode* snode_intersection(SNode* list1, SNode* list2);

SNode* snode_intersection_custom(SNode* list1, SNode* list2, int (*compare)(int, int));

void snode_sort(SNode* list, int (*compare)(int, int));

SNode* snode_reverse(SNode* list);

SNode* snode_intercalate(SNode* list1, SNode* list2);

SNode* snode_slice(SNode* list);

void snode_free(SNode* list);

void snode_print(SNode* list);

SList* slist_init(int arr[], size_t len);

int slist_empty(SList* list);

void slist_append_start(SList* list, int data);

void slist_append_end(SList* list, int data);

void slist_free(SList* list);

void slist_visit(SList* list, void (*f)(int));

void slist_print(SList* list);

#endif