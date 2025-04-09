#include "rbtree.h"

RedBlackTree::RedBlackTree() {
    root = nullptr;
}

RedBlackTree::~RedBlackTree() {
    deleteTree(root);
}

void RedBlackTree::deleteTree(Node* node) {
    if (node) {
        deleteTree(node->leftChild);
        deleteTree(node->rightChild);
        delete node;
    }
}
