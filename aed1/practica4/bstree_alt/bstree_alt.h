#ifndef __BSTREE_ALT_H__
#define __BSTREE_ALT_H__

#include "../../utils.h"

typedef enum {
  BTREE_ORDER_IN,  /** Inorder */
  BTREE_ORDER_PRE, /** Preorder */
  BTREE_ORDER_POST /** Postorder */
} BSTreeOrder;

typedef struct _BSTree *BSTree;

/**
 * Returns an empty binary search tree
*/
BSTree bstee_init(CopyFunction copy, CompareFunction cmp,
                DestroyFunction destroy);

/**
 * Destroys tree and its data
*/
void bstree_destroy(BSTree tree);

/**
 * Returns 1 if data is found on the tree, 0 otherwise
*/
int bstree_search(BSTree tree, void *data);

/**
 * Inserts a non repeated element on the tree, preserving the
 * binary search tree structure
*/
void bstree_insert(BSTree tree, void *data);

/**
 * Depth First Search iteration of the tree
 */
void bstree_visit(BSTree tree, BSTreeOrder order, ExtraVisitFunction visit,
                     void *extra);

#endif // __BSTREE_ALT_H__