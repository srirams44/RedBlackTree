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

void RedBlackTree::add(int value) {
    if (!root) { //if no tree
        root = new Node(value);
        root->parent = nullptr; //root has no parent
        return;
    }
    root = addHelper(root, value, nullptr);
}

Node* RedBlackTree::addHelper(Node* node, int value, Node* parent) {
    if (!node) {
        Node* newNode = new Node(value);
        newNode->parent = parent;
        return newNode;
    }

    if (value < node->data) { //if less, go to the left child
        node->leftChild = addHelper(node->leftChild, value, node);
    }
    else if (value > node->data) { //if more, go to the right child
        node->rightChild = addHelper(node->rightChild, value, node);
    }
    //if duplicate do nothing

    return node;
}

