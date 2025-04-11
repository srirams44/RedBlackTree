#include "node.h"
//comment for commit

Node::Node(int val) {
    data = val;
    parent = leftChild = rightChild = nullptr;
    color = red;
}

Node::~Node() {
    data = 0;
    leftChild = rightChild = parent = nullptr;
}

