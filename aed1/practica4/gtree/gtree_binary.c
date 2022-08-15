#include "gtree.h"
#include <stdlib.h>
#include <assert.h>

struct _GTNode {
		void *data; // Data of the node
		GTree bro; // Pointer to next brother
		GTree child; // Pointer to first child
};

GTree gtree_init() { return NULL; }

static GTree gtree_create_node(void *data, CopyFunction copy) {
	GTree node = malloc(sizeof(struct _GTNode));
	assert(node != NULL);
	node->data = copy(data);
	node->child = gtree_init();
	node->bro = gtree_init();
	return node;
}

int gtree_empty(GTree tree) { return tree == NULL; }

int gtree_leaf(GTree tree) {
	return gtree_empty(tree) || tree->child == NULL;
}

void gtree_destroy(GTree tree, DestroyFunction destroy) {
	if (tree == NULL)
		return;
	gtree_destroy(tree->child, destroy);
	gtree_destroy(tree->bro, destroy);
	destroy(tree->data);
	free(tree);
}

static int gtree_add_impl(GTree tree, void *parent_data, void *data,
							CopyFunction copy, CompareFunction cmp) {
	if (tree == NULL)
		return 0;
	
	if (cmp(parent_data, tree->data) == 0) {
		GTree new_node = gtree_create_node(data, copy);
		new_node->bro = tree->child;
		tree->child = new_node;
		return 1;
	}
	
	int inserted;
	// If data was recursively inserted on some node, stop 
	inserted = gtree_add_impl(tree->child, parent_data, data, copy, cmp);
	if (inserted)
		return 1;
	
	// Return the state determining if data was inserted or not
	return gtree_add_impl(tree->bro, parent_data, data, copy, cmp);
}

GTree gtree_add(GTree tree, void *parent_data, void *data,
								CopyFunction copy, CompareFunction cmp) {
	if (gtree_empty(tree))
		return gtree_create_node(data, copy);
	(void) gtree_add_impl(tree, parent_data, data, copy, cmp);
	return tree;
}

void gtree_iter(GTree tree, ExtraVisitFunction visit,
													void *extra) {
  if (gtree_empty(tree))
		return;
	visit(tree->data, extra);
	gtree_iter(tree->child, visit, extra);
	gtree_iter(tree->bro, visit, extra);
}

// Increment count every time the function is called
static inline void count(void *data, unsigned *count) {
	(void) data; // Avoid compiler warnings
	++(*count);
}

unsigned gtree_nnodes(GTree tree) {
	unsigned counter = 0;
	gtree_iter(tree, (ExtraVisitFunction) count, (void*) &counter);
	return counter;
}
