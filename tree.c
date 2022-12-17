#include "tree.h"

void update_level(treeNodePtr root, treeNodePtr  node){
    if (node != NULL){
        if (node == root->leftChild) node->number = (root->number) * 2 + 1;
        else node->number = (root->number) * 2 + 2;
        update_level(node, node->leftChild );
        update_level(node, node->rightChild);
    }
}

void node_insert(treeNodePtr *root, int key){
    if (*root == NULL){
        treeNodePtr tmp = malloc(sizeof(treeNode));
        tmp->key = key;
        tmp->number = 0;
        tmp->leftChild = NULL;
        tmp->rightChild = NULL;
        *root = tmp;
    }
    else{
        treeNodePtr currPtr = *root, prevPtr;
        while(currPtr != NULL){
            prevPtr = currPtr;
            if (currPtr->key > key) currPtr = currPtr->leftChild;
            else currPtr = currPtr->rightChild;
        }
        currPtr = malloc(sizeof(treeNode));
        currPtr->key = key;
        currPtr->rightChild = NULL;
        currPtr->leftChild = NULL;
        if (prevPtr->key > key) prevPtr->leftChild = currPtr;
        else prevPtr->rightChild = currPtr;
    }
    update_level(*root, (*root)->leftChild);
    update_level(*root, (*root)->rightChild);
}

treeNodePtr search(treeNodePtr *root, int key){
    treeNodePtr tmp = *root;
    if ((tmp == NULL) || (tmp->key == key)) return tmp;
    if (key < tmp->key) return search(&(tmp->leftChild), key);
    else return search(&(tmp->rightChild), key);
}

treeNodePtr find_parent(treeNodePtr *root, int childKey){
    treeNodePtr parent = *root;
    if (parent->key == childKey) return NULL;
    else{
        if (parent->key > childKey){
            if (parent->leftChild->key == childKey) return parent;
            else return find_parent(&parent->leftChild, childKey);
        }
        else{
            if (parent->rightChild->key == childKey) return parent;
            else return find_parent(&parent->rightChild, childKey);
        }
    }
}

treeNodePtr min(treeNodePtr root){
    treeNodePtr l = root;
    while(l->leftChild != NULL) l = l->leftChild;
    return l;
}

treeNodePtr max(treeNodePtr root){
    treeNodePtr m = root;
    while(m->rightChild != NULL) m = m->rightChild;
    return m;
}

treeNodePtr next_node(treeNodePtr root){
    treeNodePtr p = root, l = NULL;
    if (p->rightChild != NULL)
        return min(p->rightChild);
    l = find_parent(&p, l->key);
    while((l != NULL) && (p == l->rightChild)){
        p = l;
        l = find_parent(&root, l->key);
    }
    return l;
}

void delete_root(treeNodePtr *root){
    treeNodePtr tmp = *root;
    if (tmp->rightChild == NULL && tmp->leftChild == NULL){
        free(tmp);
        *root = NULL;
    }
    else if (tmp->rightChild == NULL && tmp->leftChild != NULL){
        *root = tmp->leftChild;
        free(tmp);
    }
    else if (tmp->rightChild != NULL && tmp->leftChild == NULL){
        *root = tmp->rightChild;
        free(tmp);
    }
    else{
        treeNodePtr next = next_node(tmp);
        treeNodePtr parent = find_parent(root, next->key);
        if (next->rightChild != NULL)
            parent->leftChild = next->rightChild;
        else parent->leftChild = NULL;
        tmp->key = next->key;
        free(next);
    }
}

void delete_node(treeNodePtr *root, int key){
    treeNodePtr  l = NULL, m = NULL;
    l = search(root, key);
    if (l != NULL){
        if (l != *root){
            if ((l->leftChild == NULL) && (l->rightChild == NULL)){
                m = find_parent(root, l->key);
                if (l == m->rightChild) m ->rightChild = NULL;
                else m->leftChild = NULL;
                free(l);
            }

            else if ((l -> leftChild == NULL) && (l -> rightChild != NULL))
            {
                m = find_parent(root, l->key);
                if (l == m->rightChild) m->rightChild = l -> rightChild;
                else m->leftChild = l->rightChild;
                free(l);
            }

            else if ((l->leftChild != NULL) && (l->rightChild == NULL))
            {
                m = find_parent(root, l->key);
                if (l == m->rightChild) m->rightChild = l->leftChild;
                else m->leftChild = l->leftChild;
                free(l);
            }

            else if ((l->leftChild != NULL) && (l->rightChild != NULL))
            {
                m = next_node(l);
                l -> key = m -> key;
                if (m -> rightChild == NULL)
                    find_parent(root, m->key)->leftChild = NULL;
                else find_parent(root, m->key)->leftChild = m->rightChild;
                free(m);
            }
        }
        else delete_root(root);
    }
}

void pre_order(treeNodePtr node){
    if (node != NULL){
        printf("%3d ", node->key);
        pre_order(node->leftChild);
        pre_order(node->rightChild);
    }
}

void in_order(treeNodePtr node){
    if (node != NULL){
        in_order(node->leftChild);
        printf("%3d ", node->key);
        in_order(node->rightChild);
    }
}

void post_order(treeNodePtr node){
    if (node != NULL){
        post_order(node->leftChild);
        post_order(node->rightChild);
        printf("%3d ", node->key);
    }
}

void calc_order(treeNodePtr node, int *n){
    if (node != NULL){
        if (node->number > *n) *n = node->number;
        calc_order(node->leftChild, n);
        calc_order(node->rightChild, n);
    }
}

void fill_array(treeNodePtr node, int *arr){
    if (node != NULL){
        arr[node->number] = node->key;
        fill_array(node->leftChild, arr);
        fill_array(node->rightChild, arr);
    }
}

int getNum(treeNodePtr root){
    int n = 0;
    calc_order(root,&n);
    return n;
}

void print_tree(treeNodePtr root){
    int n = getNum(root);
    int pow = 0;
    int num = 1;
    while (1){
        if (n >= num - 1){
            num *= 2;
            pow++;
        }
        else break;
    }
    int arr[num];
    for (int i = 0; i < num; ++i) {
        arr[i] = 0;
    }
    fill_array(root, arr);

    for (int i = 0, lim = 1, pos = 0; i < pow; ++i, lim *= 2) {
        int amountOfSpaces = ((num - lim) * 3) / 4;
        for (int k = 0; k < amountOfSpaces; ++k) {
            printf(" ");
        }
        for (int j = 0; j < lim; ++j, ++pos) {
            if (arr[pos] == 0) printf("   ");
            else printf(" %d ", arr[pos]);
        }
        printf("\n");
    }
}

int height(treeNodePtr root)
{
    if (root == NULL) {
        return 0;
    }
    else if (root->leftChild == NULL&&root->rightChild == NULL) {
        return 0;
    }
    else if (height(root->leftChild) > height(root->rightChild))
        return height(root->leftChild) + 1;
    else
        return height(root->rightChild) + 1;
}

