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


void RedBlackTree::search(int value) {
    if (!root) {
        cout << "Tree is empty." << endl;
        return;
    }
    searchHelper(root, value);
}

void RedBlackTree::searchHelper(Node* current, int value) {
    if (!current) {
        cout << "Value is not in tree." << endl;
        return;
    }
    if (value == current->data) {
        cout << value << " is in tree." << endl;
        return;
    }
    if (value > current->data) { //if target value is larger then node value, go to right child
        searchHelper(current->rightChild, value);
    }
    else { //if target value is not larger or equal to, must be smaller, go to left child
        searchHelper(current->leftChild, value);
    }
}

void RedBlackTree::deleteValue(int value) {
    if (!root) {
        cout << "Nothing to delete." << endl;
        return;
    }
    root = deleteHelper(root, value);
}

Node* RedBlackTree::findMin(Node* node) {
    if (!node) return nullptr;
    while (node->leftChild != nullptr) {
        node = node->leftChild;
    }
    return node;
}


/*
Node* RedBlackTree::deleteHelper(Node* node, int value) {
    if (!node) { // Base case, if node is not found
        cout << "Node not found." << endl;
        return nullptr;
    }

    // Navigate to the node to delete
    if (value < node->data) { // If value is less, go left
        node->leftChild = deleteHelper(node->leftChild, value);
    }
    else if (value > node->data) { // If value is greater, go right
        node->rightChild = deleteHelper(node->rightChild, value);
    }
    else { // found node to delete
        // Case 1 n 2: Node has at most one child
        if (!node->leftChild || !node->rightChild) {
            Node* temp = node->leftChild ? node->leftChild : node->rightChild;

            // No child case
            if (!temp) {
                temp = node;
                // If were deleting a black node, we need to fix tree properties
                if (temp->color == black) {
                    fixDelete(node);
                }

                // Update parent pointers
                if (node->parent) {
                    if (node == node->parent->leftChild) {
                        node->parent->leftChild = nullptr;
                    } else {
                        node->parent->rightChild = nullptr;
                    }
                } else {
                    root = nullptr;
                }

                delete temp;
                return nullptr;
            }
            else {
                // One child case
                Color originalColor = node->color;

                // Copy data from child and update pointers
                temp->parent = node->parent;

                if (!node->parent) {
                    root = temp;
                } else if (node == node->parent->leftChild) {
                    node->parent->leftChild = temp;
                } else {
                    node->parent->rightChild = temp;
                }

                delete node;

                // If original color was black, fix tree properties
                if (originalColor == black) {
                    fixDelete(temp);
                }

                return temp;
            }
        }
        else { // Case 3: Node has two children
            // Find successor (minimum in right subtree)
            Node* successor = findMin(node->rightChild);

            // Copy successor data
            node->data = successor->data;

            // Delete the successor
            node->rightChild = deleteHelper(node->rightChild, successor->data);
        }
    }

    return node;
}

*/
Node* RedBlackTree::deleteHelper(Node* node, int value) {
    if (!node) {
        cout << "Node not found." << endl;
        return nullptr;
    }

    if (value < node->data) {
        node->leftChild = deleteHelper(node->leftChild, value);
        if (node->leftChild) node->leftChild->parent = node;
    } else if (value > node->data) {
        node->rightChild = deleteHelper(node->rightChild, value);
        if (node->rightChild) node->rightChild->parent = node;
    } else {
        if (!node->leftChild || !node->rightChild) {
            Node* temp = node->leftChild ? node->leftChild : node->rightChild;
            Color originalColor = node->color;

            if (!temp) {
                if (node == root) {
                    root = nullptr;
                } else {
                    if (originalColor == black) {
                        fixDelete(node);
                    }
                    if (node->parent->leftChild == node) {
                        node->parent->leftChild = nullptr;
                    } else {
                        node->parent->rightChild = nullptr;
                    }
                }
                delete node;
                return nullptr;
            } else {
                temp->parent = node->parent;
                if (!node->parent) {
                    root = temp;
                } else {
                    if (node == node->parent->leftChild) {
                        node->parent->leftChild = temp;
                    } else {
                        node->parent->rightChild = temp;
                    }
                }
                delete node;
                if (originalColor == black) {
                    fixDelete(temp);
                }
                return temp;
            }
        } else {
            // Node has two children - CORRECTED APPROACH
            Node* successor = findMin(node->rightChild);
            node->data = successor->data;
            node->rightChild = deleteHelper(node->rightChild, successor->data);
            if (node->rightChild) node->rightChild->parent = node;
        }
    }
    return node;
}
/*
void RedBlackTree::fixDelete(Node* node) {
    if (!node) { //if node is nullptr, nothing to fix
        cout << "Node not found." << endl;
        return;
    }
    //continue fixing until node is root or red
    while (node != root and node->color == black) {
        //when node is a left child
        if (node == node->parent->leftChild) {
            Node* sibling = node->parent->rightChild;

            //case 1: sibling is red
            if (sibling and sibling->color == red) {
                sibling->color = black; //change sibling to black
                node->parent->color = red; //change parent to red
                rotateLeft(node->parent); //left rotation on parent
                sibling = node->parent->rightChild; //update sibling pointer
            }
            //case 2: sibling is black with both black children
            if (sibling and
                (!sibling->leftChild or sibling->leftChild->color == black) and
                (!sibling->rightChild or sibling->rightChild->color == black)) {
                sibling->color; //change sibling to red
                node = node->parent; //move node pointer up to parent
            }
            else if (sibling) {
                //case 3: sibling is black with red left child and black right child
                if (!sibling->rightChild or sibling->rightChild->color == black) {
                    if (sibling->leftChild) { //set siblings left child to black
                        sibling->leftChild->color = black;
                    }
                    sibling->color = red; //change sibling to red
                    rotateRight(sibling); //right rotation on sibling
                    sibling = node->parent->rightChild; //update sibling pointer
                    //this now transfers into case 4
                }
                //case 4: sibling is black with red right child
                sibling->color = node->parent->color; //set sibling color to parent color
                node->parent->color = black; //set parent to black
                if (sibling->rightChild) { //set siblings right child to black
                    sibling->rightChild->color = black;
                }
                rotateLeft(node->parent); //left rotation on parent
                node = root; //change node to root
            }
            else {
                node = node->parent; //if sibling is null, move up the tree
            }
        }
        //when node is a right child
        else {
            Node* sibling = node->parent->leftChild;

            //case 1: sibling is red
            if (sibling and sibling->color == red) {
                sibling->color = black; //change sibling to black
                node->parent->color = red; //change parent to red
                rotateRight(node->parent); //right rotation on parent
                sibling = node->parent->leftChild; //update sibling pointer
            }
            //case 2: sibling is black with both black children
            if (sibling and sibling->color == red) {
                sibling->color = black; //change sibling to black
                node->parent->color = red; //change parent to red
                rotateRight(node->parent); //right rotation on parent
                sibling = node->parent->leftChild; //update sibling pointer
            }
            //case 2: sibling is black with both black children
            if (sibling and
                (!sibling->rightChild or sibling->rightChild->color == black) and
                (!sibling->leftChild or sibling->leftChild->color == black)) {
                sibling->color = red; //change sibling to red
                node = node->parent; //move node pointer up to parent
            }
            else if (sibling) {
                //case 3: sibling is black with red right child and black left child
                if (!sibling->leftChild or sibling->leftChild->color == black) {
                    //change siblings right child to black
                    if (sibling->rightChild) {
                        sibling->rightChild->color = black;
                    }
                    sibling->color = red; //change sibling to red
                    rotateLeft(sibling); //left rotation on sibling
                    sibling = node->parent->leftChild; //update sibling pointer
                    //now becomes case 4
                }
                //case 4: sibling is black with red left child
                sibling->color = node->parent->color; //set siblings color to parents color
                node->parent->color = black; //set parent to black
                if (sibling->leftChild) { //set siblings left child to black
                    sibling->leftChild->color = black;
                }
                rotateRight(node->parent); //right rotate on parent
                node = root; //node becomes root to exit
            }
            else {
                node = node->parent; //if sibling is null, move up tree
            }
        }
    }
    //finally ensure node is black
    node->color = black;
}
*/
void RedBlackTree::fixDelete(Node* node) {
    if (!node) {
        cout << "Node not found." << endl;
        return;
    }

    while (node != root && node->color == black) {
        if (node == node->parent->leftChild) {
            Node* sibling = node->parent->rightChild;

            // Case 1: sibling is red
            if (sibling && sibling->color == red) {
                sibling->color = black;
                node->parent->color = red;
                rotateLeft(node->parent);
                sibling = node->parent->rightChild;
            }

            // Case 2: sibling is black with both black children
            if (sibling &&
                (!sibling->leftChild || sibling->leftChild->color == black) &&
                (!sibling->rightChild || sibling->rightChild->color == black)) {
                sibling->color = red; // FIXED: Was doing nothing
                node = node->parent;
            } else if (sibling) {
                // Case 3: sibling is black with red left child, black right child
                if (!sibling->rightChild || sibling->rightChild->color == black) {
                    if (sibling->leftChild) {
                        sibling->leftChild->color = black;
                    }
                    sibling->color = red;
                    rotateRight(sibling);
                    sibling = node->parent->rightChild;
                }

                // Case 4: sibling is black with red right child
                sibling->color = node->parent->color;
                node->parent->color = black;
                if (sibling->rightChild) {
                    sibling->rightChild->color = black;
                }
                rotateLeft(node->parent);
                node = root;
            } else {
                node = node->parent;
            }
        } else {
            Node* sibling = node->parent->leftChild;

            // Case 1: sibling is red
            if (sibling && sibling->color == red) {
                sibling->color = black;
                node->parent->color = red;
                rotateRight(node->parent);
                sibling = node->parent->leftChild;
            }

            // Case 2: sibling is black with both black children
            // FIXED: Removed duplicate case 1 and corrected condition
            if (sibling &&
                (!sibling->rightChild || sibling->rightChild->color == black) &&
                (!sibling->leftChild || sibling->leftChild->color == black)) {
                sibling->color = red;
                node = node->parent;
            } else if (sibling) {
                // Case 3: sibling is black with red right child, black left child
                if (!sibling->leftChild || sibling->leftChild->color == black) {
                    if (sibling->rightChild) {
                        sibling->rightChild->color = black;
                    }
                    sibling->color = red;
                    rotateLeft(sibling);
                    sibling = node->parent->leftChild;
                }

                // Case 4: sibling is black with red left child
                sibling->color = node->parent->color;
                node->parent->color = black;
                if (sibling->leftChild) {
                    sibling->leftChild->color = black;
                }
                rotateRight(node->parent);
                node = root;
            } else {
                node = node->parent;
            }
        }
    }

    node->color = black;
}

/*
fix until node is root or node is red, either case color black and done
cases when node is left child
 case 1: sibling is red
 - change sibling to black
 - change parent to red
 - left rotation on parent
 - update sibling pointer (new sibling should be black)

 case 2: sibling is black with both black children
 - change sibling to red
 - move node pointer up to the parent
 - continue the loop with parent as the new node

 case 3: sibling is black with red left child and black right child
 - change siblings left child to black
 - change sibling to red
 - right rotation on sibling
 - update sibling pointer
 case 3 will then change into case 4

 case 4: sibling is black with red right child
 - set sibling color to parent color
 - set parent to black
 - set siblings right child to black
 - left rotate on parent
 - change node to root and exit


case when node is a right child
case 1: sibling is red
- change sibling to black
- change parent to red
- right rotate on parent
- update sibling pointer

case 2: sibling is black with both black children
- change sibling to red
- move node pointer up to parent
- continue the loop with parent as the new node

case 3: sibling is black with red right child and black left child
- change siblings right child to black
- change sibling to red
- left rotate on sibling
- update sibling pointer
- transforms to case 4

case 4: sibling is black with red left child
- set sibling's color to parent's color
- set parent to black
- set siblings left child to black
- right rotate on parent
- node becomes root and exit

final step - ensure node is black



 Steps for deleting nodes
 * 1. If node to be deleted has no children, simply remove and update parent node
 * 2. If node to be deleted has only one child, replace node with its child.
 * 3. If node to be deleted has two children, replace node with in-order successor.
 * 4. To fix violations, color changes and rotations must be performed on nodes in tree.
 */

