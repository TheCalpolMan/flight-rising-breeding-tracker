#ifndef BINARYTREEPOSSIBILITYNODE_H
#define BINARYTREEPOSSIBILITYNODE_H

#include "binarytreenode.h"

#include <memory>

#include "dragonpossibility.h"

class BinaryTreePossibilityNode : public BinaryTreeNode
{
public:
    BinaryTreePossibilityNode(const BinaryTreeNode& rootNode, const std::vector<Dragon>& possibleParents);

    std::shared_ptr<DragonPossibility> possibility;
private:
    BinaryTreePossibilityNode() = default;
};

#endif // BINARYTREEPOSSIBILITYNODE_H
