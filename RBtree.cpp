#include <iostream>
#include "Vector.hpp"
#include "RBnode.cpp"
using namespace std;

class RBtree {
public:
    RBnode *root;
    int size=0;

    RBtree(){
        root = nullptr;
    }

    RBnode* getroot(){
        return root;
    }

    void inOrder(RBnode* root, Vector<stock>& vec) {
        if (root != nullptr) {
            inOrder(root->left, vec);
            vec.push_back(root->data);
            inOrder(root->right, vec);
        }
    }

    void rightRotation(RBnode *node){
        RBnode* tempRight  = node->left->right;
        RBnode* tempLeft = node->left;

        node->left = tempRight;
        if(tempRight != nullptr)
            tempRight->parent = node;
        
        if(node->parent == nullptr)
            root = tempLeft;
        else if(node->parent->left == node)
            node->parent->left = tempLeft;
        else
            node->parent->right = tempLeft;
        
        tempLeft->right = node;
        tempLeft->parent = node->parent;
        node->parent = tempLeft;
    }

    void leftRotation(RBnode *node){
        RBnode* tempLeft  = node->right->left;
        RBnode* tempRight = node->right;

        node->right = tempLeft;
        if(tempLeft != nullptr)
            tempLeft->parent = node;
        
        if(node->parent == nullptr)
            root = tempRight;
        else if(node->parent->left == node)
            node->parent->left = tempRight;
        else
            node->parent->right = tempRight;
        
        tempRight->left = node;
        tempRight->parent = node->parent;
        node->parent = tempRight;
    }

    void insertElement(stock data) {
        RBnode* node = new RBnode(data);
        this->root = this->insert(this->root, node);
        fixInsert(node);
        size++;
    }

    RBnode* insert(RBnode* root, RBnode* newNode) {
        if (root == nullptr)
            return newNode;

        if (root->data.close >= newNode->data.close) {
            root->left = this->insert(root->left, newNode);
            root->left->parent = root;
        } else {
            root->right = this->insert(root->right, newNode);
            root->right->parent = root;
        }
        return root;
    }

    void fixInsert(RBnode* node) {
        while (node != this->root && node->parent->color == RED) {
            RBnode* parent = node->parent;
            RBnode* grandParent = parent->parent;
            RBnode* uncle = nullptr;

            // left side
            if (parent == grandParent->left) {
                uncle = grandParent->right;
                // case I
                if (uncle != nullptr && uncle->color == RED) {
                    uncle->color = BLACK;
                    parent->color = BLACK;
                    grandParent->color = RED;
                    // now focus on grandparent node
                    node = grandParent;
                } else {
                    // case II
                    if (node == parent->right) {
                        this->leftRotation(parent);
                        parent = node;
                        node = parent->parent;
                    }
                    // case III
                    grandParent->color = RED;
                    parent->color = BLACK;
                    this->rightRotation(grandParent);
                }
            } else { // right side
                uncle = grandParent->left;
                // case I
                if (uncle != nullptr && uncle->color == RED) {
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    grandParent->color = RED;
                    // now focus on grandparent node
                    node = grandParent;
                } else {
                    if (node == parent->left) {
                        // case II
                        this->rightRotation(parent);
                        parent = node;
                        node = parent->parent;
                    }
                    // case III
                    grandParent->color = RED;
                    parent->color = BLACK;
                    this->leftRotation(grandParent);
                }
            }
        }
        this->root->color = BLACK;
    }
};