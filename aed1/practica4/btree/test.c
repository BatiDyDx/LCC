#include "btree.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static void print_int(int data) {
    printf("%d ", data);
}

int main() {
    BTree ll = btree_join(1, btree_init(), btree_init());
    BTree l = btree_join(2, ll, btree_init());
    BTree rr = btree_join(5, btree_init(), btree_init());
    BTree r = btree_join(3, btree_init(), rr);
    BTree root = btree_join(4, l, r);

    BTree copy = btree_copy(root);
    copy = btree_join(10, btree_init(), copy);
    assert(btree_search(copy, 5) == 1);
    assert(btree_sum(copy) == 25);

    assert(btree_empty(btree_init()));
    assert(!btree_empty(ll));
    assert(btree_leaf(ll));
    assert(!btree_leaf(r));
    assert(btree_nnodes(root) == 5);
    assert(!btree_search(root, 6));
    assert(btree_search(root, 5));

    assert(btree_nnodes_depth(root, 0) == 1);
    assert(btree_nnodes_depth(root, 1) == 2);
    assert(btree_nnodes_depth(root, 2) == 2);

    assert(btree_height(root) == 2);
    assert(btree_sum(root) == 15);

    printf("Preorder iterative: ");
    btree_preorder_iter(root, print_int);
    puts("");
    printf("Preorder: ");
    btree_visit(root, BTREE_PREORDER, print_int);
    puts("");
    printf("Postorder: ");
    btree_visit(root, BTREE_POSTORDER, print_int);
    puts("");
    printf("Inorder: ");
    btree_visit(root, BTREE_INORDER, print_int);
    puts("");
    btree_destroy(root);
    btree_destroy(copy);

    return 0;
}
