#ifndef __AVL_H__
#define __AVL_H__

#include "../../utils.h"

typedef enum {
  AVL_INORDER,  /** Inorder */
  AVL_PREORDER, /** Preorder */
  AVL_POSTORDER /** Postorder */
} AVL_VisitOrder;

typedef struct _AVL *AVL;

/**
 * Returns an empty AVL tree
 */
AVL avl_init(CopyFunction, CompareFunction, DestroyFunction);

/**
 * Destroys tge tree and its data
 */
void avl_destroy(AVL);

/**
 * Returns 1 if data is in the tree, 0 otherwise
 */
int avl_search(AVL, void *);

/**
 * Inserts a non repeated element in the tree, preserving the
 * properties of an AVL tree
 */
void avl_insert(AVL, void *);

/**
 * Returns 1 if the tree is an AVL, 0 otherwise
 */
int avl_check(AVL);

/**
 * DSF iteration over the tree
 */
void avl_visit(AVL, AVL_VisitOrder, ExtraVisitFunction, void *);

#endif /* __AVL_H__*/