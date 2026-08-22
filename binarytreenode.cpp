#include "binarytreenode.h"

#include <iostream>

std::string BinaryTreeNode::toString() const
{
    std::stringstream stream;
    writeToStream("", this, false, stream);

    return stream.str();
}

bool BinaryTreeNode::isLeaf() const
{
    return (leftChild == nullptr && rightChild == nullptr);
}

int BinaryTreeNode::getMaxDepth() const
{
    if (isLeaf())
    {
        return 1;
    }

    return std::max(leftChild->getMaxDepth(), rightChild->getMaxDepth()) + 1;
}

int BinaryTreeNode::getBranchCount() const
{
    if (isLeaf())
    {
        return 0;
    }

    int score = 0;

    if (!leftChild->isLeaf() && !rightChild->isLeaf())
    {
        score++;
    }

    return score + leftChild->getBranchCount() + rightChild->getBranchCount();
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
