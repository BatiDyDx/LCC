#include "gtree.h"
#include "../../practica2/glist.h"
#include <stdlib.h>
#include <assert.h>

struct _GTNode {
	void *data; // Data of the node
	GList children; // List of its children
};

static inline void* id(void *p) { return p; }

GTree gtree_init() { return NULL; }

static GTree gtree_create_node(void *data, CopyFunction copy) {
	GTree node = malloc(sizeof(struct _GTNode));
	assert(node != NULL);
	node->data = copy(data);
	node->children = glist_init();
	return node;
}

int gtree_empty(GTree tree) { return tree == NULL; }

int gtree_leaf(GTree tree) {
	return gtree_empty(tree) || glist_empty(tree->children);
}

void gtree_destroy(GTree tree, DestroyFunction destroy) {
	GList tmp;
  for (GList node = tree->children; node != NULL; node = tmp) {
		tmp = node->next;
		gtree_destroy((GTree)node->data, destroy);
		free(node);
	}
	destroy(tree->data);
	free(tree);
}

static int gtree_add_impl(GTree tree, void *parent_data, void *data,
							CopyFunction copy, CompareFunction cmp) {
	if (cmp(parent_data, tree->data) == 0) {
		GTree new_node = gtree_create_node(data, copy);
		tree->children = glist_append_start(tree->children, new_node, id);
		return 1;
	}
	int inserted = 0;
	GList node;
	for (node = tree->children; node != NULL && !inserted; node = node->next) {
		// If data was recursively inserted on some node, stop 
		inserted = gtree_add_impl((GTree)node->data, parent_data, data, copy, cmp);
	}
	// Return the state determining if data was inserted or not
	return inserted;
}

GTree gtree_add(GTree tree, void *parent_data, void *data,
					CopyFunction copy, CompareFunction cmp) {
	if (gtree_empty(tree)) {
		return gtree_create_node(data, copy);
	}
	(void) gtree_add_impl(tree, parent_data, data, copy, cmp);
	return tree;
}

void gtree_iter(GTree tree, ExtraVisitFunction visit, void *extra) {
	visit(tree->data, extra);
	for (GList child = tree->children; child != NULL; child = child->next)
		gtree_iter((GTree) child->data, visit, extra);
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
