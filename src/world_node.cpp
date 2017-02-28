#include "world_node.h"

#include <cassert>

WorldNode::WorldNode()
    : children()
    , parent(nullptr)
{
}

void WorldNode::attachChild(Ptr child)
{
    child->parent = this;
    children.push_back(std::move(child));
}

/*
 * Finds. removes and returns child node
 */
WorldNode::Ptr WorldNode::detachChild(const WorldNode& node)
{
    //First find the node in the container
    assert(!children.empty());
    auto it = children.begin();
    for (; it != children.end(); ++it)
    {
        if ((*it).get() == &node)
            break;
    }
    //Make sure the node was in the container
    assert(it != children.end());

    Ptr found = std::move(*it);
    found->parent = nullptr;
    children.erase(it);
    return found;
}

void WorldNode::update(sf::Time deltaTime)
{
    updateCurrent(deltaTime);
    updateChildren(deltaTime);
}

void WorldNode::updateCurrent(sf::Time deltaTime)
{
    //Do nothing by default
}

void WorldNode::updateChildren(sf::Time deltaTime)
{
    for (const Ptr& child : children)
        child->update(deltaTime);
}

/*
 * Applies transform of the current node and draws the node and its
 * children with the new transform
 */
void WorldNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    drawCurrent(target, states);
    drawChildren(target, states);
}

void WorldNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    //Do nothing by default
}

void WorldNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const Ptr& child : children)
        child->draw(target, states);
}

sf::Vector2f WorldNode::getWorldPosition() const
{
    return getWorldTransform() * sf::Vector2f();
}

/*
 * Applies all transforms traveling through parents until we reac
 * the root node, to compute the absolute world transform instead
 * of the transform relative to the parent
 */
sf::Transform WorldNode::getWorldTransform() const
{
    sf::Transform trans = sf::Transform::Identity;
    for (const WorldNode* node = this; node != nullptr; node = node->parent)
        trans = node->getTransform() * trans;

    return trans;
}
