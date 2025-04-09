#ifndef NODE_H
#define NODE_H
#include <iostream>
using namespace std;

enum Color {
    red,
    black
};
struct Node {
    Node(int val);
    ~Node();
    int data;
    Node* parent;
    Node* leftChild;
    Node* rightChild;
    Color color;
};



#endif //NODE_H
