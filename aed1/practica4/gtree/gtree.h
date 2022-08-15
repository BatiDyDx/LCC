#ifndef __GTREE_H__
#define __GTREE_H__ // General Generic Tree

#include "../../utils.h"

typedef struct _GTNode *GTree;

/**
 * Returns a generic empty tree
 */
GTree gtree_init();


/**
 * Determines if the tree is empty
 */
int gtree_empty(GTree tree);

/*
 * Determines if the tree is a leaf. Returns 1 if tree is a leaf or empty,
 * 0 otherwise
*/
int gtree_leaf(GTree tree);

/**
 * Destroys the tree
 */
void gtree_destroy(GTree tree, DestroyFunction destroy);

/**
 * Add a leaf node to the tree with the data given. The new node is added as a
 * child of the node in the tree that matches with parent_data. If the tree
 * is empty, add the node as the root node.
 */
GTree gtree_add(GTree tree, void *parent_data, void *data,
					CopyFunction copy, CompareFunction cmp);

/**
 * Iterate over the tree, extra is used to carry information over each node
 */
void gtree_iter(GTree tree, ExtraVisitFunction visit,
						  void *extra);

/**
 * Returns the number of nodes in the tree
 */
unsigned gtree_nnodes(GTree tree);

#endif /** __GTREE_H__ */