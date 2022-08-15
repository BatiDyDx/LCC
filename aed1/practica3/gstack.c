#include "gstack.h"

GStack gstack_init() { return NULL; }

void gstack_free(GStack s, DestroyFunction destroy) { glist_free(s, destroy); }

int gstack_empty(GStack s) { return glist_empty(s); }

void* gstack_top(GStack s, CopyFunction copy) { return copy(s->data); }

GStack gstack_push(GStack s, void* data, CopyFunction copy) {
    return glist_append_start(s, data, copy);
}

GStack gstack_pop(GStack s, DestroyFunction destroy) {
    return glist_remove_start(s, destroy);
}

void gstack_print(GStack s, VisitFunction print) { glist_visit(s, print); }

GList glist_reverse(GList list, CopyFunction copy) {
    GStack stack = gstack_init();

    for (GNode *tmp = list; list != NULL; list = list->next)
        gstack_push(stack, tmp->data, copy);

    // In this implementation, GStack is an alias for GList
    return stack;
}
