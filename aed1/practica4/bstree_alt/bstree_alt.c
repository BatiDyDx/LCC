#include "bstree_alt.h"
#include <assert.h>
#include <stdlib.h>

/**
 * Alternative implementation for binary search trees.
 * Two levels of abstraction are maintained:
 * The lower level implements BST with void* data
 * The higher level encapsulates the BST structure and the copy, compare and
 * destroy functions. User must communicate with the higher level, which
 * handles calls to the lower level with appropiate paramters
*/

/**
 * Lower Level:
 * ===============
 */

/**
 * Binary Search Tree node structure
 * Holds a pointer to data, and two pointers for its left and right
 * subtrees respectively
 */
typedef struct _BST_Node {
  void *data;
  struct _BST_Node *left, *right;
} BST_Node;

/**
 * The lower level functions are static, so the user cannot use them directly
*/
static void bstree_node_destroy(BST_Node *root, DestroyFunction destroy) {
  if (root != NULL) {
    bstree_node_destroy(root->left, destroy);
    bstree_node_destroy(root->right, destroy);
    destroy(root->data);
    free(root);
  }
}

static int bstree_node_search(BST_Node *root, void *data,
                              CompareFunction cmp) {
  if (root == NULL)
    return 0;
  else if (cmp(data, root->data) == 0) // root->data == data
    return 1;
  else if (cmp(data, root->data) < 0) // data < root->data
    return bstree_node_search(root->left, data, cmp);
  else // root->data < data
    return bstree_node_search(root->right, data, cmp);
}

static BST_Node *bstree_node_insert(BST_Node *root, void *data,
                                  CopyFunction copy, CompareFunction cmp) {
  if (root == NULL) { // Insert data on new node
    BST_Node *new_node = malloc(sizeof(struct _BST_Node));
    assert(new_node != NULL);
    new_node->data = copy(data);
    new_node->left = new_node->right = NULL;
    return new_node;
  }
  else if (cmp(data, root->data) < 0) // data < root->data
    root->left = bstree_node_insert(root->left, data, copy, cmp);
  else if (cmp(data, root->data) > 0) // root->data < data
    root->right = bstree_node_insert(root->right, data, copy, cmp);
  // If data was alredy in the tree, do not replace it
  return root;
}

static void bstree_node_visit(BST_Node *root, BSTreeOrder order,
                                 ExtraVisitFunction visit, void *extra) {
  if (root != NULL) {
    if (order == BTREE_ORDER_PRE)
      visit(root->data, extra);
    bstree_node_visit(root->left, order, visit, extra);
    if (order == BTREE_ORDER_IN)
      visit(root->data, extra);
    bstree_node_visit(root->right, order, visit, extra);
    if (order == BTREE_ORDER_POST)
      visit(root->data, extra);
  }
}

/**
 * Higher level:
 * ===============
 */

/**
 * Binary Search Tree structure.
 * Holds a pointer to the root node of the tree (root),
 * a pointer to a copy function that receives data and returns a pointer to a
 * physical copy of data (copy), a pointer to a function that compares data
 * to insert in the tree (cmp), a pointer to a destroy function to free data
 * when the tree is destroyed (destroy)
 */
struct _BSTree {
  BST_Node *root;
  CopyFunction copy;
  CompareFunction cmp;
  DestroyFunction destroy;
};

BSTree bstee_init(CopyFunction copy, CompareFunction cmp,
                  DestroyFunction destroy) {
  BSTree tree = malloc(sizeof(struct _BSTree));
  assert(tree != NULL);
  tree->root = NULL;
  tree->copy = copy;
  tree->cmp = cmp;
  tree->destroy = destroy;
  return tree;
}

void bstree_destroy(BSTree tree) {
  bstree_node_destroy(tree->root, tree->destroy);
  free(tree);
}

int bstree_search(BSTree tree, void *data) {
  return bstree_node_search(tree->root, data, tree->cmp);
}

void bstree_insert(BSTree tree, void *data) {
  tree->root = bstree_node_insert(tree->root, data, tree->copy, tree->cmp);
}

void bstree_visit(BSTree tree, BSTreeOrder order,
                     ExtraVisitFunction visit, void *extra) {
  bstree_node_visit(tree->root, order, visit, extra);
}
