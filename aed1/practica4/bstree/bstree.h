#ifndef __BSTREE_H__
#define __BSTREE_H__

#include "../../utils.h"

typedef enum {
    BSTREE_INORDER,  /** Inorder */
    BSTREE_PREORDER, /** Preorder */
    BSTREE_POSTORDER /** Postorder */
} BSTreeVisitOrder;

typedef struct _BST_Node* BSTree;

/*
 ** Returns an empty binary search tree
*/
BSTree bstree_init();

/**
 ** Indicates if the tree is empty
*/
int bstree_empty(BSTree tree);

/*
 ** Destroy a BST
*/
void bstree_destroy(BSTree tree, DestroyFunction destroy);

/*
 ** Returns 1 if data is in the tree, 0 otherwise
*/
int bstree_search(BSTree tree, void* data, CompareFunction cmp);

/*
 ** Inserts data in the tree (preserving the BST structure)
*/
BSTree bstree_insert(BSTree tree, void* data, CopyFunction copy, CompareFunction cmp);

/*
 ** Removes an element of the tree, if possible (preserving the BST structure)
*/
BSTree bstree_delete(BSTree root, void* data, DestroyFunction destroy,
	CompareFunction cmp);

/*
 ** Returns the k minimum element in the tree
*/
void* bstree_k_min(BSTree root, int k);

/*
 ** DSF run over the tree
*/
void bstree_visit(BSTree tree, BSTreeVisitOrder order, ExtraVisitFunction visit,
    void* extra);

/*
 ** Return the maximum (rightmost element) of the tree, or NULL
 ** if the tree is empty
*/
void* bstree_max(BSTree root, CopyFunction copy);

/*
 ** Return the minimum (leftmost element) of the tree, or NULL
 ** if the tree is empty
*/
void* bstree_min(BSTree root, CopyFunction copy);

/*
 ** Checks if a given tree is a binary search tree
*/
int bstree_check(BSTree root, CompareFunction cmp);

#endif //__BSTREE_H__