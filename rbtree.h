#ifndef RBTREE_H
#define RBTREE_H
#include "node.h"



class RedBlackTree {
public:
    RedBlackTree();
    ~RedBlackTree();
    void add(int value);
    void print();
private:
    Node* root;
    void deleteTree(Node* node);
    Node* addHelper(Node* node, int value, Node* parent, Node* &insertedNode);
    void fixInsert(Node* node);
    void rotateLeft(Node* x);
    void rotateRight(Node* y);
    void printHelper(Node* node, int level);

};



#endif //RBTREE_H
