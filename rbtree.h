#ifndef RBTREE_H
#define RBTREE_H
#include "node.h"


class RedBlackTree {
public:
    RedBlackTree();
    ~RedBlackTree();
    void add(int value);
    void print();
    void deleteValue(int value);
    void search(int value);
private:
    Node* root;
    void deleteTree(Node* node);
    Node* addHelper(Node* node, int value, Node* parent, Node* &insertedNode);
    void fixInsert(Node* node);
    void rotateLeft(Node* x);
    void rotateRight(Node* y);
    void printHelper(Node* node, int level);
    void searchHelper(Node* current, int value);
    //Node* deleteHelper(Node* node, int value);
    Node* findMin(Node* node);
    void fixDelete(Node* node, Node* parent);
    Node* findNode(int value);
    void deleteNode(Node* node);
    void transplant(Node* a, Node* b);
    Node* getSibling(Node* node);

};



#endif //RBTREE_H
