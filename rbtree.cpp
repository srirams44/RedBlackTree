#include "rbtree.h"
#include <queue>

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
        root->color = black;
        return;
    }
    Node* insertedNode = nullptr;
    root = addHelper(root, value, nullptr, insertedNode);
    fixInsert(insertedNode); //fix violations to redBlacktree after inserting
}

Node* RedBlackTree::addHelper(Node* node, int value, Node* parent, Node* &insertedNode) {
    if (!node) {
        Node* newNode = new Node(value);
        newNode->parent = parent;
        insertedNode = newNode;
        return newNode;
    }


    if (value < node->data) { //if less, go to the left child
        node->leftChild = addHelper(node->leftChild, value, node, insertedNode);
    }
    else if (value > node->data) { //if more, go to the right child
        node->rightChild = addHelper(node->rightChild, value, node, insertedNode);
    }
    //if duplicate do nothing

    return node;
}


void RedBlackTree::rotateLeft(Node* x) {
    Node* y = x->rightChild; //right child of x
    x->rightChild = y->leftChild; //y's left child becomes x's right child
    if (y->leftChild) {
        y->leftChild->parent = x; //if leftchild of y isnt nullptr, update
    }
    y->parent = x->parent; //make y's parent the same as x's parent

    if (!x->parent) {
        root = y; //if x was the root, make y the new root
    }
    else if (x == x->parent->leftChild) {
        x->parent->leftChild = y; //if x was a left child, y becomes the left child
    }
    else {
        x->parent->rightChild = y; //if x was a right child, y becomes the right child
    }
    y->leftChild = x; //x becomes the left child of y
    x->parent = y; //update x's parent to y
}

void RedBlackTree::rotateRight(Node* y) {
    Node* x = y->leftChild; //left child of y
    y->leftChild = x->rightChild; //x's right child becomes y's left child
    if (x->rightChild != nullptr) {
        x->rightChild->parent = y; //update the parent of x's right child
    }
    x->parent = y->parent; //make x's parent the same as y's parent

    if (!y->parent) {
        root = x; //if y was the root, make x the new root
    }
    else if (y == y->parent->rightChild) {
        y->parent->rightChild = x; //if y was a right child, x becomes the right child
    }
    else {
        y->parent->leftChild = x; //if y was a left child, x becomes the left child
    }

    x->rightChild = y; //y becomes the right child of x
    y->parent = x; //update y's parent to x
}

void RedBlackTree::fixInsert(Node* node) {
    //this function will fix the red-black tree properties after insertion
    while (node != root and node->parent->color == red) {
        //keep fixing until either the root or the parent is black
        Node* parent = node->parent;
        Node* grandparent = parent->parent;

        if (parent == grandparent->leftChild) {
            //if parent is the child of the grandparent
            Node* uncle = grandparent->rightChild; //sibling of the parent

            if (uncle and uncle->color == red) {
                //if uncle is red, just recolor
                parent->color = black;
                uncle->color = black;
                grandparent->color = red;
                node = grandparent; //move up tree and continue checking
            }
            else {
                //node is right child, rotate left
                if (node == parent->rightChild) {
                    node = parent;
                    rotateLeft(node);
                }
                //node is left child, rotate right and fix colors
                parent = node->parent;
                grandparent = parent->parent;
                parent->color = black;
                grandparent->color = red;
                rotateRight(grandparent);
            }
        }
        else {
            //same logic as bove, but mirrored for when parent is a right child
            Node* uncle = grandparent->leftChild;
            //if uncle is red, recolor
            if (uncle and uncle->color == red) {
                parent->color = black;
                uncle->color = black;
                grandparent->color = red;
                node = grandparent;
            }
            else {
                //if node is left child, rotate right first
                if (node == parent->leftChild) {
                    node = parent;
                    rotateRight(node);
                }

                //node is right child, rotate left and recolor
                parent = node->parent;
                grandparent = parent->parent;
                parent->color = black;
                grandparent->color = red;
                rotateLeft(grandparent);
            }
        }
    }

    root->color = black; //make sure root is always black
}

void RedBlackTree::print() {
    printHelper(root, 0);
}

void RedBlackTree::printHelper(Node* node, int level) {
    if (node == nullptr) {
        return;
    }

    printHelper(node->rightChild, level + 1); // Print right subtree first

    for (int i = 0; i < level; ++i) {
        cout << "\t"; // Indent for level
    }

    // Print node data + color
    cout << node->data;
    if (node->color == black) {
        cout << "B";
    } else {
        cout << "R";
    }
    cout << endl;

    printHelper(node->leftChild, level + 1); // Then print left subtree
}