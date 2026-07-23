#include "binarytreenode.h"

#include <iostream>

BinaryTreeNode::BinaryTreeNode() {}

void BinaryTreeNode::print()
{
    privatePrint("", this, false);
}

void BinaryTreeNode::privatePrint(const std::string &prefix, const BinaryTreeNode* node, bool isLeft)
{
    // stolen and adapted from https://stackoverflow.com/a/51730733
    // thank you!!

    if( node != nullptr )
    {
        std::cout << prefix;

        std::cout << (isLeft ? "|--" : "l--" );

        // print the value of the node
        std::cout << "O" << std::endl;

        // enter the next tree level - left and right branch
        privatePrint( prefix + (isLeft ? "|  " : "   "), &*node->leftChild, true);
        privatePrint( prefix + (isLeft ? "|  " : "   "), &*node->rightChild, false);
    }
}
