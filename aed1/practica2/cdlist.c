#include "cdlist.h"

CDList* cdlist_init(int arr[], size_t len) {
    if (len == 0)
        return NULL;

    CDList *head = NULL, *tail, *tmp;
    for (int i = len; i > 0; i--) {
        tmp = malloc(sizeof(CDList));
        assert(tmp != NULL);
        tmp->data = arr[i - 1];
        tmp->next = head;
        if (head != NULL)
            head->prev = tmp;
        head = tmp;
    }
    // Move forward until the last element (tail of the list)
    for (tail = head; tail->next != NULL; tail = tail->next);
    head->prev = tail;
    tail->next = head;

    return head;
}

int cdlist_empty(CDList* head) { return head == NULL; }

size_t cdlist_len(CDList* head) {
    if (cdlist_empty(head))
        return 0;

    size_t len = 1;
    for (CDList* tmp = head->next; tmp != head; tmp = tmp->next, len++);
    return len;
}

int cdlist_contains(CDList* head, int data) {
    int finished_cycle = 0;
    for (CDList* tmp = head; !finished_cycle; tmp = tmp->next) {
        if (tmp->data == data)
            return 1;
        else if (tmp == head->prev)
            finished_cycle = 1;
    }
    return 0;
}

int cdlist_index(CDList* head, int data) {
    int finished_cycle = 0, i = 0;
    for (CDList* tmp = head; !finished_cycle; tmp = tmp->next, i++) {
        if (tmp->data == data)
            return i;
        else if (tmp == head->prev)
            finished_cycle = 1;
    }
    return -1;
}

CDList* cdlist_insert(CDList* head, size_t pos, int data) {
    CDList* node = malloc(sizeof(CDList));
    assert(node != NULL);
    node->data = data;
    if (cdlist_empty(head)) {
        node->next = node->prev = NULL;
        return node;
    }

    // Avoid iterating around the list many times. An example of this is:
    // For a list of 5 elements, position 9 is the same as position 4
    pos = pos % cdlist_len(head);
    CDList* tmp = head;

    // Terminar de encontrar bug, no se puede
    // asignar tmp = tmp->next por alguna razon
    for (size_t i = 0; i < pos; i++) {
        tmp = tmp->next;
    }

    tmp->prev->next = node;
    node->prev = tmp->prev;
    node->next = tmp;
    tmp->prev = node;

    return head;
}

CDList* cdlist_delete(CDList* head, size_t pos) {
    if (cdlist_empty(head))
        return NULL;
    else if (head == head->next) {
        // List of length 1
        free(head);
        return NULL;
    }

    pos = pos % cdlist_len(head);
    CDList* tmp = head;
    for (int i = 0; i++ < pos; tmp = tmp->next);

    tmp->prev->next = tmp->next;
    tmp->next->prev = tmp->prev;

    if (pos == 0)
        head = head->next;

    free(tmp);

    return head;
}

void cdlist_free(CDList* head) {
    if (cdlist_empty(head))
        return ;
    CDList *last = head->prev, *tmp = head;
    while (head != last) {
        tmp = head->next;
        free(head);
        head = tmp;
    }
    // Last if freed independently to avoid accesing already freed nodes
    free(last);
}

void cdlist_print(CDList* head, size_t offset) {
    for (int i = 0; i < offset; i++, head = head->next);
    int finished_cycle = 0;
    printf("[ ");
    for (CDList* tmp = head; !finished_cycle; tmp = tmp->next) {
        printf("%d, ", tmp->data);
        if (tmp == head->prev)
            finished_cycle = 1;
    }
    printf("]\n");
}

void cdlist_visit(CDList* head, void (*f)(int)) {
    int finished_cycle = 0;
    for (CDList* tmp = head; !finished_cycle; tmp = tmp->next) {
        f(tmp->data);
        if (tmp == head->prev)
            finished_cycle = 1;
    }
}

