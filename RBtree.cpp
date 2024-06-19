// #include <iostream>
// #include "RBnode.cpp"
// using namespace std;

// class RBtree {
// private:
//     RBnode *root;

//     void rightRotation(RBnode *node){
//         RBnode* tempRight  = node->left->right;
//         RBnode* tempLeft = node->left;

//         node->left = tempRight;
//         if(tempRight != nullptr)
//             tempRight->parent = node;
        
//         if(node->parent == nullptr)
//             root = tempLeft;
//         else if(node->parent->left == node)
//             node->parent->left = tempLeft;
//         else
//             node->parent->right = tempLeft;
        
//         tempLeft->right = node;
//         tempLeft->parent = node->parent;
//         node->parent = tempLeft;
//     }

//     void leftRotation(RBnode *node){
//         RBnode* tempLeft  = node->right->left;
//         RBnode* tempRight = node->right;

//         node->right = tempLeft;
//         if(tempLeft != nullptr)
//             tempLeft->parent = node;
        
//         if(node->parent == nullptr)
//             root = tempRight;
//         else if(node->parent->left == node)
//             node->parent->left = tempRight;
//         else
//             node->parent->right = tempRight;
        
//         tempRight->left = node;
//         tempRight->parent = node->parent;
//         node->parent = tempRight;
//     }

// };