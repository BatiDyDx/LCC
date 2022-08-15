#include <string.h>
#include "slist.h"
#include "dlist.h"
#include "cdlist.h"
#include "glist.h"
#include "sglist.h"
#include "../contact.h"

int gt(int x, int y) {
    if (x < y)
        return 1;
    else if (x > y)
        return -1;
    return 0;
}

void test_snode() {
    /* ------ Declaracion de listas ------- */
    SNode* list1 = snode_init((int[3]) {1, 2, 3}, 3);
    SNode* list2 = snode_init((int[2]) {10, 50}, 2);
    SNode* shuffled_list = snode_init((int [5]) {5, 2, 8, 3, 6}, 5);
    /* ------------------------------------ */

    /* ---- Pruebas en listas enlazadas --- */
    snode_print(list1);
    
    assert(snode_len(list1) == 3);
    assert(snode_contains(list1, 3));
    assert(!snode_contains(list1, 5));
    assert(snode_index(list1, 2) == 1);
    assert(snode_index(list1, 4) == -1);

    snode_link(list1, list2);

    assert(snode_len(list1) == 5);
    assert(snode_contains(list1, 50));
    assert(snode_index(list1, 50) == 4);
    snode_print(list1);

    SNode* intersection = snode_intersection(list1, list2);
    snode_print(intersection);
    assert(snode_len(intersection) == 2);
    assert(snode_contains(intersection, 50) == 1);

    SNode* list3 = snode_slice(list1);
    snode_print(list1);

    snode_sort(shuffled_list, gt);
    snode_print(shuffled_list);

    snode_free(list1);
    snode_free(list3);
    snode_free(shuffled_list);
}

void test_slist() {
    SList* list = slist_init((int [5]) {1, 2, 4, 8, 16}, 5);

    slist_append_end(list, 32);
    assert(snode_index(list->first, 32) == 5);

    slist_append_start(list, 0);
    assert(snode_contains(list->first, 0));

    snode_print(list->first);

    slist_free(list);
}

void test_dlist() {
    DList* list = dlist_init((int[5]) {1, 5, 3, 8, 22}, 5);

    assert(!dlist_contains(list, 71));
    dlist_append_last(list, 71);
    assert(dlist_contains(list, 71));

    dlist_append_start(list, 10);
    assert(dlist_index(list, 10) == 0);
    assert(dlist_index(list, 22) == 5);
    assert(dlist_index(list, 2) == -1);

    dlist_print(list);
    assert(dlist_len(list) == 7);

    dlist_insert(list, 0, 52);
    
    assert(!dlist_insert(list, 9, 97));
    dlist_insert(list, 8, 97);
    dlist_insert(list, 5, 51);
    assert(dlist_index(list, 51) == 5);
    assert(dlist_len(list) == 10);

    assert(!dlist_delete(list, 10));
    dlist_delete(list, 9);
    assert(!dlist_contains(list, 97));

    for (int i = 0; i < 9; i++)
        dlist_delete(list, 0);
    assert(list->first == NULL && list->last == NULL);

    dlist_print(list);
    dlist_free(list);
}

void test_cdlist() {
    CDList* clist = cdlist_init((signed[6]) {1, 2, -4, 67, 102, -23}, 6);

    assert(cdlist_len(clist) == 6);
    cdlist_print(clist, 3);

    cdlist_insert(clist, 2, -69);
    assert(cdlist_len(clist) == 7);
    assert(cdlist_contains(clist, -69));
    assert(!cdlist_contains(clist, 69));
    assert(cdlist_index(clist, 67) == 4);

    clist = cdlist_delete(clist, 7);
    assert(cdlist_len(clist) == 6);
    assert(!cdlist_contains(clist, 1));
    assert(cdlist_index(clist, 2) == 0);

    cdlist_free(clist);
}

int filter_age(Contact *contact) {
    return contact->age <= 60;
}

void test_glist() {
    GList list = glist_init(), filtered_list;
    Contact *contacts[6];
    contacts[0] = contact_init("Pepe Argento", "3412695452", 61);
    contacts[1] = contact_init("Moni Argento", "3412684759", 60);
    contacts[2] = contact_init("Coqui Argento", "3415694286", 32);
    contacts[3] = contact_init("Paola Argento", "3416259862", 29);
    contacts[4] = contact_init("Maria Elena Fuseneco", "3416874594", 59);
    contacts[5] = contact_init("Dardo Fuseneco", "3416894526", 64);

    for (int i = 0; i < 6; ++i) {
        list =
            glist_append_start(list, contacts[i], (CopyFunction)contact_copy);
        contact_free(contacts[i]);
    }
    filtered_list = glist_filter(list, (CopyFunction)contact_copy, (Predicate)filter_age);
    glist_visit(filtered_list, (VisitFunction)contact_print);

    glist_free(list, (DestroyFunction)contact_free);
    glist_free(filtered_list, (DestroyFunction)contact_free);
}

/* copy function that returns copy of a string */
char* copy_string(char *src) {
    char* dest = malloc(strlen(src) * sizeof(char));
    assert(dest != NULL);
    strcpy(dest, src);
    return (void*) dest;
}

void test_sglist() {
    void* names[6] = {"bati", "pau", "rich", "franco", "nahuel", "joaquin"};
    SGList list = sglist_from_array(names, 6, (CopyFunction)copy_string, (CompareFunction)strcmp);
    sglist_visit(list, (VisitFunction)puts);
	puts("");

    assert(!sglist_search(list, "angelo", (CompareFunction)strcmp));

    list = sglist_insert(list, "angelo", (CopyFunction)copy_string, (CompareFunction)strcmp);
	list = sglist_insert(list, "panchi", (CopyFunction)copy_string, (CompareFunction)strcmp);
	
	assert(sglist_search(list, "angelo", (CompareFunction)strcmp));
    sglist_visit(list, (VisitFunction)puts);

    sglist_free(list, (DestroyFunction)free);
}

int main() {
    test_snode();
    test_slist();
    test_dlist();
    test_cdlist();
    test_glist();
    test_sglist();
    return 0;
}
