#include "avl.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Note: In the following diagrams, [ X ] is a node called X, and < A > is a
 * subtree called A. For example
 *     [ X ]
 *     /   \
 *   < A >  [ Y ]
 *             \
 *             [ Z ]
 * The diagram represents the tree with node X, left subtree A, root of its right
 * subtree Y, with only a right child Z.
 * 
 * Links on the diagrams may not be to scale. The diference between lines is
 * what indicates the height of each node or subtree
*/   

/**
 * Structure of an AVL node
 * Contains a pointer to data, a pointer
 * to the root node of the left subtree and a
 * pointer to the root of the right subtree and
 * an int to represent the height of the tree
 */
typedef struct _AVL_Node {
  void *data;
  struct _AVL_Node *left, *right;
  int height;
} *AVL_Node;

/**
 * Structure of an AVL tree
 * It contains a pointer to the root node,
 * a pointer to a copy function (which receives data and returns
 * a copy), a pointer to a compare function that compares two values
 * and returns a negative integer if the first one is less than the
 * second one, 0 if they are equal, or a positive integer otherwise,
 * a pointer to a destroy function that receives data and destroys it.
 * In this implementation, the pointers to the functions needed to manipulate
 * data are stored in the structure to avoid passing them as arguments to
 * the functions that handle the AVL behaviour.
 */
struct _AVL {
  AVL_Node root;
  CopyFunction copy;
  CompareFunction cmp;
  DestroyFunction destroy;
};

AVL avl_init(CopyFunction copy, CompareFunction cmp,
  DestroyFunction destroy) {
  AVL tree = malloc(sizeof(struct _AVL));
  assert(tree != NULL);
  tree->root = NULL;
  tree->copy = copy;
  tree->cmp = cmp;
  tree->destroy = destroy;
  return tree;
}

/**
 * avl_init_node: Internal function that creates a new node and
 * returns it. The height of a leaf is 0
 */
static AVL_Node avl_init_node(void* data, CopyFunction copy) {
  AVL_Node new_node = malloc(sizeof(struct _AVL_Node));
  assert(new_node != NULL);
  new_node->data = copy(data);
  new_node->left = new_node->right = NULL;
  new_node->height = 0;
  return new_node;
}

static void avl_destroy_node(AVL_Node root, DestroyFunction destroy) {
  if (root != NULL) {
    // destroys the nodes in postorder
    avl_destroy_node(root->left, destroy);
    avl_destroy_node(root->right, destroy);
    destroy(root->data);
    free(root);
  }
}

void avl_destroy(AVL tree) {
  avl_destroy_node(tree->root, tree->destroy);
  free(tree);
}

static int avl_search_node(AVL_Node root, CompareFunction cmp, void* data) {
  if (root == NULL)
    return 0;
  else if (cmp(data, root->data) == 0) // root->data == data
    return 1;
  else if (cmp(data, root->data) < 0) // data < root->data
    return avl_search_node(root->left, cmp, data);
  else // root->data < data
    return avl_search_node(root->right, cmp, data);
}

int avl_search(AVL tree, void* data) {
  return avl_search_node(tree->root, tree->cmp, data);
}

/**
 * avl_node_height: Internal function that returns the height of a node
 * The height of an empty tree is defined to be -1
 */
static inline int avl_node_height(AVL_Node root) {
  return (root == NULL ? -1 : root->height);
}

/**
 * avl_max_children_height_node: Internal function that returns the max
 * height of its children.
 */
static unsigned avl_max_children_height_node(AVL_Node root) {
  assert(root != NULL);
  int left_height = avl_node_height(root->left);
  int right_height = avl_node_height(root->right);
  return (left_height < right_height ? right_height : left_height);
}

/**
 * avl_node_balance_factor: Internal function that returns the balance
 * factor of a node
 */
static int avl_node_balance_factor(AVL_Node root) {
  assert(root != NULL);
  int factor = avl_node_height(root->right) - avl_node_height(root->left);
  assert(-2 <= factor && factor <= 2);
  return factor;
}

/**
 * avl_simple_rotation_left: Internal function that handles a simple
 * left rotation and returns the new root
 *       [ X ]                       [ Y ]
 *       /   \                       /    \
 *     < A > [ Y ]       ==>      [ X ]    \
 *           /   \                /   \     \
 *        < B >   \            < A > < B >  < C >
 *                < C >           
 */
static AVL_Node avl_simple_rotation_left(AVL_Node root) {
  AVL_Node right_child = root->right;
  assert(right_child != NULL);
  // update pointers
  root->right = right_child->left;
  right_child->left = root;
  // update heights
  root->height = 1 + avl_max_children_height_node(root);
  right_child->height = 1 + avl_max_children_height_node(right_child);
  return right_child;
}


/**
 * avl_simple_rotation_right: Internal function that handles a simple
 * right rotation and returns the new root
 *       [ X ]                       [ Y ]
 *       /   \                       /    \
 *    [ Y ]   < A >    ==>          /    [ X ]
 *    /   \                        /     /   \
 *   /  < B >                  < C >  < B > < A >
 * < C >
*/
static AVL_Node avl_simple_rotation_right(AVL_Node root) {
  AVL_Node left_child = root->left;
  assert(left_child != NULL);
  // update pointers
  root->left = left_child->right;
  left_child->right = root;
  // update heights
  root->height = 1 + avl_max_children_height_node(root);
  left_child->height = 1 + avl_max_children_height_node(left_child);
  return left_child;
}

static AVL_Node avl_node_insert(AVL_Node root, void* data,
  CopyFunction copy, CompareFunction cmp) {
  if (root == NULL) // Insert the new element
    return avl_init_node(data, copy);
  else if (cmp(data, root->data) < 0) { // data must go in the left subtree
    root->left = avl_node_insert(root->left, data, copy, cmp);
    // check balance
    if (avl_node_balance_factor(root) == -2) {
      // Insertion on right subtree of left child
      if (avl_node_balance_factor(root->left) == 1)
        root->left = avl_simple_rotation_left(root->left);
      root = avl_simple_rotation_right(root);
    }
    root->height = 1 + avl_max_children_height_node(root);
  } else if (cmp(data, root->data) > 0) { // data must go in the right subtree
    root->right = avl_node_insert(root->right, data, copy, cmp);
    // check balance
    if (avl_node_balance_factor(root) == 2) {
      // Insertion on left subtree of right child
      if (avl_node_balance_factor(root->right) == -1)
        root->right = avl_simple_rotation_right(root->right);
      root = avl_simple_rotation_left(root);
    }
    root->height = 1 + avl_max_children_height_node(root);
  }
  return root; // dont add repeated elements
}

void avl_insert(AVL tree, void* data) {
  tree->root = avl_node_insert(tree->root, data, tree->copy, tree->cmp);
}

/**
 * avl_check: Returns 1 if the tree is an AVL, 0 otherwise
 * avl_node_check_bst: Internal function that returns 1 if the tree is a binary
 * search tree, 0 otherwise
 * avl_node_check_height_and_balance: Internal function that returns 1 if the
 * height and balance of the nodes are correct, 0 otherwise
*/
static int avl_node_check_bst(AVL_Node root, void* min, void* max,
  CompareFunction cmp) {
  // The empty tree is a valid BST
  if (root == NULL)
    return 1;
  else {
    // check left, right and root match the order
    if (min != NULL && cmp(root->data, min) <= 0)
      return 0;
    if (max != NULL && cmp(max, root->data) <= 0)
      return 0;
    // check recursively subtrees
    return (avl_node_check_bst(root->left, min, root->data, cmp) &&
      avl_node_check_bst(root->right, root->data, max, cmp));
  }
}
static int avl_node_check_height_and_balance(AVL_Node root) {
  // The empty tree is correctly balanced
  if (root == NULL)
    return 1;
  // validate recursively subtrees
  int ret1 = avl_node_check_height_and_balance(root->left);
  int ret2 = avl_node_check_height_and_balance(root->right);
  if (ret1 && ret2) {
    // If subtrees are valid, check height and balance of root
    int height = 1 + avl_max_children_height_node(root);
    int balance = avl_node_balance_factor(root);
    if ((root->height == height) && (balance >= -1) && (balance <= 1))
      return 1;
  }
  // If one of the subtrees is not balanced, return false
  return 0;
}

int avl_check(AVL tree) {
  return (avl_node_check_height_and_balance(tree->root) &&
    avl_node_check_bst(tree->root, NULL, NULL, tree->cmp));
}

/**
 * avl_visit: Recorrido DFS del tree
*/
static void avl_node_visit(AVL_Node root, AVL_VisitOrder order,
                          ExtraVisitFunction visit, void* extra) {
  if (root != NULL) {
    if (order == AVL_PREORDER)
      visit(root->data, extra);
    avl_node_visit(root->left, order, visit, extra);
    if (order == AVL_INORDER)
      visit(root->data, extra);
    avl_node_visit(root->right, order, visit, extra);
    if (order == AVL_POSTORDER)
      visit(root->data, extra);
  }
}

void avl_visit(AVL tree, AVL_VisitOrder order, ExtraVisitFunction visit,
  void* extra) {
  avl_node_visit(tree->root, order, visit, extra);
}
