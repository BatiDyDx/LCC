#include "dlist.h"

DList* dlist_init(int arr[], size_t len) {
    DList* list = malloc(sizeof(DList));
    assert(list != NULL);
    list->first = NULL;
    list->last = NULL;
    for (int i = 0; i < len; i++)
        dlist_append_last(list, arr[i]);
    return list;
}

int dlist_empty(DList* list) { return list->first == NULL; }

void dlist_append_start(DList* list, int data) {
    DNode* new_node = malloc(sizeof(DNode));
    assert(new_node != NULL);

    new_node->data = data;
    new_node->prev = NULL;
    new_node->next = list->first;

    if (!dlist_empty(list))
        list->first->prev = new_node;
    else
        list->last = new_node;
    list->first = new_node;
}

void dlist_append_last(DList* list, int data) {
    DNode* new_node = malloc(sizeof(DNode));
    assert(new_node != NULL);

    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = list->last;

    if (!dlist_empty(list))
        list->last->next = new_node;
    else
        list->first = new_node;
    list->last = new_node;
}

size_t dlist_len(DList* list) {
    size_t len = 0;
    for (DNode* tmp = list->first; tmp != NULL; tmp = tmp->next, len++);
    return len;
}

int dlist_insert(DList* list, size_t pos, int data) {
    if (pos == 0) {
        dlist_append_start(list, data);
        return 1;
    }

    DNode* tmp = list->first;
    for (size_t i = 0; i < (pos - 1) && tmp != NULL; i++, tmp = tmp->next);
    
    if (tmp == NULL)
        return 0;

    else if (tmp == list->last) {
        dlist_append_last(list, data);
        return 1;
    }

    DNode* new_node = malloc(sizeof(DNode));
    assert(new_node != NULL);

    new_node->data = data;
    new_node->next = tmp->next;
    new_node->prev = tmp;
    tmp->next->prev = new_node;
    tmp->next = new_node;

    return 1;
}

int dlist_delete(DList* list, size_t pos) {
    if (dlist_empty(list)) // Nothing can be deleted from an empty list
        return 0;

    if (pos == 0) {
        DNode* node_to_remove = list->first;
        list->first = node_to_remove->next;
        free(node_to_remove);

        if (list->first == NULL)
            list->last = NULL;

        return 1;
    }

    DNode* tmp = list->first;
    for (size_t i = 0; i < pos && tmp != NULL; i++, tmp = tmp->next);

    if (tmp == NULL)
        return 0; // Exceeded the number of elements on the list

    tmp->prev->next = tmp->next;
    if (tmp->next != NULL) {
        tmp->next->prev = tmp->prev;
    } else 
        // If were to remove the last element, update the list pointer
        list->last = tmp->prev;

    free(tmp);

    return 1;
}

int dlist_contains(DList* list, int data) {
    for (DNode* tmp = list->first; tmp != NULL; tmp = tmp->next)
        if (tmp->data == data)
            return 1;
    return 0;
}

int dlist_index(DList* list, int data) {
    int i = 0;
    for (DNode* tmp = list->first; tmp != NULL; tmp = tmp->next, i++)
        if (tmp->data == data)
            return i;
    return -1;
}

void dlist_free(DList* list) {
    DNode* tmp = list->first;
    while (!dlist_empty(list)) {
        tmp = list->first->next;
        free(list->first);
        list->first = tmp;
    }
    free(list);
}

void dlist_visit(DList* list, void (*f)(int), DLIST_VISIT_DIR dir) {
    DNode* tmp;
    if (dir == DLIST_FORWARD)
        for (tmp = list->first; tmp != NULL; tmp = tmp->next)
            f(tmp->data);
    else
        for (tmp = list->last; tmp != NULL; tmp = tmp->prev)
            f(tmp->data);
}

void dlist_print(DList* list) {
    printf("[ ");
    for (DNode* tmp = list->first; tmp != NULL; tmp = tmp->next)
        printf("%d, ", tmp->data);
    printf("]\n");
}
