#include "bstree.h"
#include <assert.h>
#include <stdlib.h>

/*
 ** Binary search tree structure
 ** Holds a pointer for data, and two pointers
 ** to the left and right subtrees respectively
*/
struct _BST_Node {
	void* data;
	struct _BST_Node *left, *right;
};

BSTree bstree_init() { return NULL; }

int bstree_empty(BSTree tree) { return tree == NULL; }

static inline int bstree_leaf(BSTree tree) {
	if (bstree_empty(tree))
		return -1;
	return bstree_empty(tree->left) && bstree_empty(tree->right);
}

void bstree_destroy(BSTree root, DestroyFunction destroy) {
	if (!bstree_empty(root)) {
		bstree_destroy(root->left, destroy);
		bstree_destroy(root->right, destroy);
		destroy(root->data);
		free(root);
	}
}

int bstree_search(BSTree root, void* data, CompareFunction cmp) {
	if (bstree_empty(root))
		return 0;
	else if (cmp(data, root->data) == 0) // root->data == data
		return 1;
	else if (cmp(data, root->data) < 0) // data < root->data
		return bstree_search(root->left, data, cmp);
	else // root->data < data
		return bstree_search(root->right, data, cmp);
}

BSTree bstree_insert(BSTree root, void* data, CopyFunction copy,
	CompareFunction cmp) {
	if (bstree_empty(root)) { // Inserts data in the new node
		struct _BST_Node* new_node = malloc(sizeof(struct _BST_Node));
		assert(new_node != NULL);
		new_node->data = copy(data);
		new_node->left = new_node->right = NULL;
		return new_node;
	}
	else if (cmp(data, root->data) < 0) // data < root->data
		root->left = bstree_insert(root->left, data, copy, cmp);
	else if (cmp(data, root->data) > 0) // root->data < data
		root->right = bstree_insert(root->right, data, copy, cmp);
	// If data is already in the tree, do nothing
	return root;
}

BSTree bstree_delete(BSTree root, void* data, DestroyFunction destroy,
	CompareFunction cmp) {

	if (bstree_empty(root))
		return NULL;
	
	int comparison = cmp(root->data, data);
	BSTree tmp = root;
	
	if (comparison < 0)
		root->right = bstree_delete(root->right, data, destroy, cmp);
	else if (comparison > 0)
		root->left = bstree_delete(root->left, data, destroy, cmp);
	else {
		if (bstree_leaf(root))
			tmp = NULL;
		else if (bstree_empty(root->left))
			tmp = root->right;
		// If right node is empty, or the left node has no right subtree
		// then the new root can be replaced by the left node
		else if (bstree_empty(root->right))
			tmp = root->left;
		else if (bstree_empty(root->left->right)) {
			tmp = root->left;
			tmp->right = root->right;
		} else {
			BSTree mvn = root->left; // mvn: max value node
			// Stop on the parent of the rightmost node
			while (mvn->right->right != NULL)
				mvn = mvn->right;
			tmp = mvn->right;
			mvn->right = tmp->left;
			tmp->left = root->left;
			tmp->right = root->right;
		}
		destroy(root->data);
		free(root);
	}
	return tmp;
}

void* _bstree_k_min_impl(BSTree root, int *k) {
	if (bstree_empty(root))
		return NULL;
	void* min = _bstree_k_min_impl(root->left, k);
	if (min != NULL)
		return min;
	if (*k == 0)
		return root->data;
	--(*k);
	return _bstree_k_min_impl(root->right, k);
}

void* bstree_k_min(BSTree root, int k) {
	return _bstree_k_min_impl(root, &k);
}

void bstree_visit(BSTree root, BSTreeVisitOrder order,
	ExtraVisitFunction visit, void* extra) {
	if (root != NULL) {
		if (order == BSTREE_PREORDER)
			visit(root->data, extra);
		bstree_visit(root->left, order, visit, extra);
		if (order == BSTREE_INORDER)
			visit(root->data, extra);
		bstree_visit(root->right, order, visit, extra);
		if (order == BSTREE_POSTORDER)
			visit(root->data, extra);
	}
}

void* bstree_max(BSTree root, CopyFunction copy) {
	if (bstree_empty(root))
		return NULL;
	if (bstree_empty(root->right))
		return copy(root->data);
	return bstree_max(root->right, copy);
}

void* bstree_min(BSTree root, CopyFunction copy) {
	if (bstree_empty(root))
		return NULL;
	if (bstree_empty(root->left))
		return copy(root->data);
	return bstree_max(root->left, copy);
}

static int bstree_check_impl(BSTree root, void *min, void *max,
                            CompareFunction cmp) {
	if (bstree_empty(root))
		return 1;
	if (min != NULL && cmp(min, root->data) > 0)
    return 0;
	if (max != NULL && cmp(max, root->data) < 0)
    return 0;
  
  return  (bstree_check_impl(root->left, min, root->data, cmp) &&
            bstree_check_impl(root->right, root->data, max, cmp));
}

int bstree_check(BSTree root, CompareFunction cmp) {
  return bstree_check_impl(root, NULL, NULL, cmp);
}
