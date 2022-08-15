#include "bstree.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 ** Test cases for general binary search trees
*/

struct _BST_Node {
	void* data;
	struct _BST_Node* left, * right;
};

#define N_WORDS 16

static void* copy_string(void* data) {
    char* str = malloc(sizeof(char) * (strlen(data) + 1));
    assert(str != NULL);
    strcpy(str, data);
    return str;
}
static int compare_string(void* data1, void* data2) {
    return strcmp(data1, data2);
}
static void destroy_string(void* data) { free(data); }
static void print_string(void* data, __attribute__((unused)) void* extra) {
    printf("\"%s\" ", (char*)data);
}

int main() {

    char* words[N_WORDS] = {"gato",      "perro",    "casa",     "persona",
                            "parque",    "arbol",    "edificio", "calle",
                            "argentina", "santa fe", "rosario",  "unr",
                            "edya",      "farmacia", "tiempo",   "celular" };

    // Create an empty tree and add words
    BSTree tree = bstree_init();
    for (int i = 0; i < N_WORDS; i++)
        tree = bstree_insert(tree, words[i], copy_string, compare_string);

    // Prints the tree inorder (alphabetically)
    printf("Inorder iteration: ");
    bstree_visit(tree, BSTREE_INORDER, print_string, NULL);
    puts("");

    // Search elements
    assert(bstree_search(tree, "farmacia", compare_string));
    assert(bstree_search(tree, "santa fe", compare_string));
    assert(bstree_search(tree, "persona", compare_string));
    assert(bstree_search(tree, "unr", compare_string));
    assert(bstree_search(tree, "argentina", compare_string));
    assert(!bstree_search(tree, "telefono", compare_string));
    assert(!bstree_search(tree, "mail", compare_string));
    assert(!bstree_search(tree, "parques", compare_string));
    assert(!bstree_search(tree, "EDyA1", compare_string));

    // Remove elements
    tree = bstree_delete(tree, "persona", destroy_string, compare_string);
    assert(!bstree_search(tree, "persona", compare_string));
    bstree_delete(tree, "camello", destroy_string, compare_string);
    tree = bstree_delete(tree, "santa fe", destroy_string, compare_string);
    tree = bstree_delete(tree, "farmacia", destroy_string, compare_string);
    tree = bstree_delete(tree, "gato", destroy_string, compare_string);
    assert(!bstree_search(tree, "santa fe", compare_string));

    printf("Inorder iteration (after deletion): ");
    bstree_visit(tree, BSTREE_INORDER, print_string, NULL);
    puts("");

    // Search minimum elements
    assert(compare_string(bstree_k_min(tree, 0), "arbol") == 0);
    assert(compare_string(bstree_k_min(tree, 3), "casa") == 0);
    assert(compare_string(bstree_k_min(tree, 8), "perro") == 0);
    assert(bstree_k_min(tree, 15) == NULL);
    
    // Validate binary search trees
    assert(bstree_check(tree, compare_string));
    
    BSTree nodes[5];
    for (int i = 0; i < 5; i++)
        nodes[i] = bstree_insert(NULL, "cabeza", copy_string, compare_string);
    printf("%s\n", nodes[0]->data);
    /*
            "perfil"
            /       \
        "imagen"    "texto"
        /      \
    "cuenta"    "seguridad"
    */
    BSTree nbs_tree = nodes[0];
    nbs_tree->data = copy_string("perfil");
    nbs_tree->right = nodes[1];
    nbs_tree->right->data = copy_string("texto");
    nbs_tree->left = nodes[2];
    nbs_tree->left->data = copy_string("imagen");
    nbs_tree->left->left = nodes[3];
    nbs_tree->left->left->data = copy_string("cuenta");
    nbs_tree->left->right = nodes[4];
    nbs_tree->left->right->data = copy_string("seguridad");
    assert(!bstree_check(nbs_tree, compare_string));

    for (int i = 0; i < 5; i++) {
        nodes[i]->right = NULL;
        nodes[i]->left = NULL;
    }

    /*
        "perfil"
        /       \
    "imagen"    "seguridad"
                /       \
            "cuenta"    "texto"
    */
    nbs_tree->left = nodes[2]; // "cuenta" "imagen" "perfil" "seguridad" "texto"
    nbs_tree->right = nodes[4];
    nbs_tree->right->left = nodes[3];
    nbs_tree->right->right = nodes[1];

    assert(!bstree_check(nbs_tree, compare_string));

    // Destroy the tree
    bstree_destroy(tree, destroy_string);
    bstree_destroy(nbs_tree, destroy_string);

    return 0;
}
