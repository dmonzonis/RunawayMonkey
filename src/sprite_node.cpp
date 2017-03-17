#include "sprite_node.h"

SpriteNode::SpriteNode(const sf::Texture& texture)
    : sprite(texture)
    , id(0)
{
}

SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect)
    : sprite(texture, textureRect)
{
}

void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}

Category::Type SpriteNode::getCategory() const
{
    return Category::Sprite;
}

void SpriteNode::setId(int id)
{
    this->id = id;
}

int SpriteNode::getId() const
{
    return id;
}

void SpriteNode::setTexture(const sf::Texture& texture)
{
    sprite.setTexture(texture);
}
