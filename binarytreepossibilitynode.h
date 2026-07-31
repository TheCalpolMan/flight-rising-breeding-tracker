#ifndef BINARYTREEPOSSIBILITYNODE_H
#define BINARYTREEPOSSIBILITYNODE_H

#include "binarytreenode.h"

#include <memory>

#include "dragonpossibility.h"

class BinaryTreePossibilityNode : public BinaryTreeNode
{
public:
    BinaryTreePossibilityNode(std::shared_ptr<BinaryTreeNode> rootNode, const std::vector<std::shared_ptr<Dragon>>& possibleParents);

    std::shared_ptr<BinaryTreePossibilityNode> castLeft() const;

    std::shared_ptr<BinaryTreePossibilityNode> castRight() const;

    void propogate();

    std::shared_ptr<DragonPossibility> possibility;
private:
    BinaryTreePossibilityNode() = default;

    BinaryTreePossibilityNode(std::shared_ptr<BinaryTreeNode> baseNode);

    bool propogated = false;
};

#endif // BINARYTREEPOSSIBILITYNODE_H
