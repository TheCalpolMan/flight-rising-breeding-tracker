#include "binarytreepossibilitynode.h"

BinaryTreePossibilityNode::BinaryTreePossibilityNode(const BinaryTreeNode &rootNode, const std::vector<Dragon>& possibleParents)
{
    // std::list<std::shared_ptr<BinaryTreeNode>> nodesToCheck = decltype(nodesToCheck)();
    // nodesToCheck.push_back(config.treeRoot);

    // int dragonIndex = 0;

    // while(!nodesToCheck.empty())
    // {
    //     std::shared_ptr<BinaryTreeNode> currentNode = nodesToCheck.front();
    //     nodesToCheck.pop_front();

    //     if (currentNode->leftChild->isLeaf() && currentNode->rightChild->isLeaf() &&
    //         config.dragons.at(dragonIndex++)->male == config.dragons.at(dragonIndex++)->male)
    //     {
    //         return false;
    //     }

    //     if (currentNode->rightChild->isLeaf())
    //     {
    //         nodesToCheck.push_front(currentNode->rightChild);
    //     }

    //     if (currentNode->leftChild->isLeaf())
    //     {
    //         nodesToCheck.push_front(currentNode->leftChild);
    //     }
    // }
}
