#ifndef BINARYTREENODE_H
#define BINARYTREENODE_H

#include <memory>
#include <string>

class BinaryTreeNode
{
public:
    BinaryTreeNode();

    void print();

    std::shared_ptr<BinaryTreeNode> leftChild;
    std::shared_ptr<BinaryTreeNode> rightChild;
private:
    static void privatePrint(const std::string& prefix, const BinaryTreeNode* node, bool isLeft);
};

#endif // BINARYTREENODE_H
