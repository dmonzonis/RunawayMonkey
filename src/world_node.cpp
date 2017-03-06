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

void WorldNode::update(sf::Time dt)
{
    updateCurrent(dt);
    updateChildren(dt);
}

void WorldNode::updateCurrent(sf::Time dt)
{
    //Do nothing by default
}

void WorldNode::updateChildren(sf::Time dt)
{
    for (const Ptr& child : children)
        child->update(dt);
}

/*
 * Applies transform of the current node and draws the node and its
 * children with the new transform
 */
void WorldNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //Apply all the transforms of the current node
    states.transform *= getTransform();

    drawCurrent(target, states);
    drawChildren(target, states);
    
    //Draw hitbox for debug purposes
    drawHitbox(target, states);
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

//Draw the hitbox to the window, for debugging purposes
void WorldNode::drawHitbox(sf::RenderTarget& target, sf::RenderStates) const
{
    sf::FloatRect rect = getHitbox();
    sf::RectangleShape shape;
    shape.setPosition(sf::Vector2f(rect.left, rect.top));
    shape.setSize(sf::Vector2f(rect.width, rect.height));
    shape.setFillColor(sf::Color(0, 255, 0, 50));
    shape.setOutlineColor(sf::Color::Red);
    shape.setOutlineThickness(1.f);

    target.draw(shape);
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

Category::Type WorldNode::getCategory() const
{
    //WorldNode has Scene category by default
    return Category::Scene;
}

void WorldNode::onCommand(const Command& command, sf::Time dt)
{
    //If node has the same category as the command, then execute it
    if (command.category == getCategory())
        command.action(*this, dt);

    //Pass the command to its children
    for (Ptr& child : children)
        child->onCommand(command, dt);
}

sf::FloatRect WorldNode::getHitbox() const
{
    return sf::FloatRect();
}

bool collision(WorldNode& a, WorldNode& b)
{
    return a.getHitbox().intersects(b.getHitbox());
}
