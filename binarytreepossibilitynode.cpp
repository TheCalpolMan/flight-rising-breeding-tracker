#include "binarytreepossibilitynode.h"

#include <list>

#include "dragonpossibilityfactory.h"

BinaryTreePossibilityNode::BinaryTreePossibilityNode(std::shared_ptr<BinaryTreeNode> rootNode, const std::vector<std::shared_ptr<Dragon>>& possibleParents) :
    BinaryTreePossibilityNode(rootNode)
{
    if (isLeaf())
    {
        return;
    }

    std::list<std::shared_ptr<BinaryTreePossibilityNode>> nodesToCheck = decltype(nodesToCheck)();
    nodesToCheck.push_front(castRight());
    nodesToCheck.push_front(castLeft());

    int dragonIndex = 0;

    while(!nodesToCheck.empty())
    {
        auto currentNode = nodesToCheck.front();
        nodesToCheck.pop_front();

        if (currentNode->isLeaf())
        {
            currentNode->possibility = DragonPossibilityFactory::getInstance().constructPossiblilty(possibleParents.at(dragonIndex));
        }

        nodesToCheck.push_front(currentNode->castRight());
        nodesToCheck.push_front(currentNode->castLeft());
    }
}

std::shared_ptr<BinaryTreePossibilityNode> BinaryTreePossibilityNode::castLeft() const
{
    return std::static_pointer_cast<BinaryTreePossibilityNode>(leftChild);
}

std::shared_ptr<BinaryTreePossibilityNode> BinaryTreePossibilityNode::castRight() const
{
    return std::static_pointer_cast<BinaryTreePossibilityNode>(rightChild);
}

void BinaryTreePossibilityNode::propogate()
{
    if (propogated)
    {
        return;
    }

    if (isLeaf())
    {
        propogated = true;
        return;
    }

    castLeft()->propogate();
    castRight()->propogate();

    possibility = DragonPossibilityFactory::getInstance().constructPossiblilty(castLeft()->possibility, castRight()->possibility);
    propogated = true;
}

BinaryTreePossibilityNode::BinaryTreePossibilityNode(std::shared_ptr<BinaryTreeNode> baseNode)
{
    if (!baseNode->leftChild->isLeaf())
    {
        leftChild = std::shared_ptr<BinaryTreePossibilityNode>(new BinaryTreePossibilityNode(baseNode->leftChild));
    }

    if (!baseNode->rightChild->isLeaf())
    {
        rightChild = std::shared_ptr<BinaryTreePossibilityNode>(new BinaryTreePossibilityNode(baseNode->rightChild));
    }
}
