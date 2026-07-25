#ifndef BINARYTREENODE_H
#define BINARYTREENODE_H

#include <memory>
#include <string>
#include <sstream>

class BinaryTreeNode
{
public:
    BinaryTreeNode() = default;

    std::string toString() const;

    bool isLeaf();

    std::shared_ptr<BinaryTreeNode> leftChild;
    std::shared_ptr<BinaryTreeNode> rightChild;
private:
    static void writeToStream(const std::string& prefix, const BinaryTreeNode* node, bool isLeft, std::stringstream& stream);
};

#endif // BINARYTREENODE_H
