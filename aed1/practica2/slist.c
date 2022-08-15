#include "slist.h"

SNode* snode_init(int arr[], size_t len) {
    SNode *head = NULL, *tmp;
    for (int i = len; i > 0; i--) {
        tmp = malloc(sizeof(SNode));
        assert(tmp != NULL);
        tmp->data = arr[i - 1];
        tmp->next = head;
        head = tmp;
    }
    return head;
}

int snode_empty(SNode* list) { return list == NULL; }

SNode* snode_append_start(SNode* list, int data) {
    SNode* new_node = malloc(sizeof(SNode));
    assert(new_node != NULL);
    new_node->data = data;
    new_node->next = list;
    return new_node;
}

SNode* snode_remove_start(SNode* list) {
    if (snode_empty(list))
        return NULL;

    SNode* tmp = list->next;
    free(list);
    return tmp;
}

SNode* snode_append_end(SNode* list, int data) {
    SNode* new_node = malloc(sizeof(SNode));
    assert(new_node != NULL);
    new_node->data = data;
    new_node->next = NULL;
    if (snode_empty(list))
        return new_node;
    SNode* tmp;
    for (tmp = list; tmp->next != NULL; tmp = tmp->next);
    tmp->next = new_node;
    return list;
}

size_t snode_len(SNode* list) {
    size_t len;
    for (len = 0; list != NULL; len++, list = list->next);
    return len;
}

SNode* snode_link(SNode* list1, SNode* list2) {
    SNode* tmp = list1;
    if (snode_empty(list1))
        return list2;
    for (; tmp->next != NULL; tmp = tmp->next);
    tmp->next = list2;
    return list1;
}

SNode* snode_insert(SNode* list, size_t pos, int data) {
    SNode* new_node = malloc(sizeof(SNode));
    assert(new_node != NULL);
    SNode* tmp = list;

    if (pos == 0)
        return snode_append_start(list, data);

    for (size_t i = 0; i < (pos - 1) && tmp != NULL; i++, tmp = tmp->next);

    if (tmp == NULL)
        return NULL;

    tmp->next = snode_append_start(tmp->next, data);
    return list;
}

SNode* snode_delete(SNode* list, size_t pos) {
    SNode* tmp;
    if (pos == 0) {
        tmp = list->next;
        free(list);
        return tmp;
    }
    tmp = list;
    for (size_t i = 0; i < (pos - 1) && tmp != NULL; i++, tmp = tmp->next);
    if (tmp == NULL)
        return NULL;
    
    tmp->next = snode_remove_start(tmp->next);
    return list;
}

int snode_contains(SNode* list, int data) {
    for (; list != NULL; list = list->next)
        if (list->data == data)
            return 1;
    return 0;
}

int snode_index(SNode* list, int data) {
    for (int i = 0; list != NULL; list = list->next, i++) {
        if (list->data == data)
            return i;
    }
    return -1;
}

SNode* snode_intersection(SNode* list1, SNode* list2) {
    SNode* inter = NULL; // Intersection list
    SNode* tmp = list2;

    for (; list1 != NULL; list1 = list1->next)
        for (list2 = tmp; list2 != NULL; list2 = list2->next)
            if (list1->data == list2->data)
                inter = snode_insert(inter, 0, list1->data);

    return inter;
}

SNode* snode_intersection_custom(SNode* list1, SNode* list2, int (*compare)(int, int)) {
    SNode* inter = NULL; // Intersection list
    SNode* tmp = list2;

    for (; list1 != NULL; list1 = list1->next)
        for (list2 = tmp; list2 != NULL; list2 = list2->next)
            if (compare(list1->data, list2->data))
                inter = snode_insert(inter, 0, list1->data);

    return inter;
}

void snode_sort(SNode* list, int (*compare)(int, int)) {
    size_t len = snode_len(list);
    int i, j;
    SNode* tmp_node;
    SNode *tmp1, *tmp2;
    for (i = 0; i < len - 1; i++) {
        tmp1 = list;
        tmp2 = list->next;
        for (j = 0; j < len - i - 1; j++) {
            if (compare(tmp1->data, tmp2->data) == -1) {
                int tmp = tmp2->data;
                tmp2->data = tmp1->data;
                tmp1->data = tmp;
            }
            if (j < len - i - 2) {
                tmp1 = tmp1->next;
                tmp2 = tmp2->next;
            }
        }
    }
}

SNode* snode_reverse(SNode* list) {
    SNode* head = NULL;
    while (list != NULL) {
        head = snode_append_start(head, list->data);
        list = list->next;
    }
    return head;
}

SNode* snode_intercalate(SNode* list1, SNode* list2) {
    SNode* new_list = NULL;
    SNode* node;
    while (list1 != NULL && list2 != NULL) {
        if (list1 != NULL)
            new_list = snode_append_start(new_list, list1->data);
        
        if (list2 != NULL)
            new_list = snode_append_start(new_list, list1->data);
        
        list1 = list1->next;
        list2 = list2->next;
    }
    return new_list;
}

SNode* snode_slice(SNode* list) {
    SNode* new_list = NULL;
    size_t half, len = snode_len(list);

    if (len % 2 == 0)
        half = len / 2;
    else
        half = ((len - 1) / 2) + 1;

    for (size_t i = 0; i < half - 1; i++)
        list = list->next;
    new_list = list->next;
    list->next = NULL;
    return new_list;
}

void snode_free(SNode* list) {
    SNode* tmp;
    while (list != NULL) {
        tmp = list;
        list = list->next;
        free(tmp);
    }
}

void snode_print(SNode* list) {
    printf("[ ");
    for (; list != NULL; list = list->next)
        printf("%d, ", list->data);
    printf("]\n");
}

// Ejercicio 3

SList* slist_init(int arr[], size_t len) {
    SList* list = malloc(sizeof(SList));
    assert(list != NULL);
    if (len == 0) {
        list->first = NULL;
        list->last = NULL;
        return list;
    }
    list->first = snode_init(arr, len);
    SNode* tmp;
    for (tmp = list->first; tmp->next != NULL; tmp = tmp->next);
    list->last = tmp;
    return list;
}

int slist_empty(SList* list) { return list->first == NULL; }

void slist_append_start(SList* list, int data) {
    list->first = snode_append_start(list->first, data);
    if (list->last == NULL)
        list->last = list->first;
}

void slist_append_end(SList* list, int data) {
    SNode* new_node = snode_append_start(NULL, data);
    if (slist_empty(list)) {
        list->last = new_node;
        list->first = new_node;
        return ;
    }
    list->last = (list->last->next = new_node);
}

void slist_free(SList* list) {
    snode_free(list->first);
    free(list);
}

void slist_visit(SList* list, void (*f)(int)) {
    for (SNode* tmp = list->first; tmp != NULL; tmp = tmp->next)
        f(tmp->data);
}

void slist_print(SList* list) {
    snode_print(list->first);
}
