#include "tree.h"



int main() {

    treeNodePtr root = NULL;

    node_insert(&root, 12);
    node_insert(&root, 5);
    node_insert(&root, 23);
    node_insert(&root, 4);
    node_insert(&root, 3);
    node_insert(&root, 15);
    node_insert(&root, 30);
    node_insert(&root, 40);
    print_tree(root);

    int treeHeight = height(root);

    printf("%d", treeHeight);

    return 0;
}
