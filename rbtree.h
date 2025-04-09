#ifndef RBTREE_H
#define RBTREE_H
#include "node.h"



class RedBlackTree {
public:
    RedBlackTree();
    ~RedBlackTree();
private:
    Node* root;
    void deleteTree(Node* node);

};



#endif //RBTREE_H
