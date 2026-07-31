#include "binarytreenode.h"

#include <iostream>

std::string BinaryTreeNode::toString() const
{
    std::stringstream stream;
    writeToStream("", this, false, stream);

    return stream.str();
}

bool BinaryTreeNode::isLeaf()
{
    return (leftChild == nullptr && rightChild == nullptr);
}

void BinaryTreeNode::writeToStream(const std::string &prefix, const BinaryTreeNode* node, bool isLeft, std::stringstream& stream)
{
    // stolen and adapted from https://stackoverflow.com/a/51730733
    // thank you!!

    if( node != nullptr )
    {
        stream << prefix;

        stream << (isLeft ? "|--" : "l--" );

        // print the value of the node
        stream << "O" << std::endl;

        // enter the next tree level - left and right branch
        writeToStream( prefix + (isLeft ? "|  " : "   "), &*node->leftChild, true, stream);
        writeToStream( prefix + (isLeft ? "|  " : "   "), &*node->rightChild, false, stream);
    }
}
