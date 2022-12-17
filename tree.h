//
// Created by zhenya on 12.11.2022.
//

#ifndef UNTITLED23_TREE_H
#define UNTITLED23_TREE_H

#include <malloc.h>
#include <stddef.h>
#include <stdio.h>

typedef struct treeNode{
    int key;
    int number;
    struct treeNode *leftChild;
    struct treeNode *rightChild;
}treeNode;

typedef treeNode *treeNodePtr;

void node_insert(treeNodePtr *, int );
void delete_node(treeNodePtr *, int);
int height(treeNodePtr root);
void pre_order(treeNodePtr);
void in_order(treeNodePtr);
void post_order(treeNodePtr);
void print_tree(treeNodePtr);


#endif //UNTITLED23_TREE_H
