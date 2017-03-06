#pragma once

#include "world_node.h"

class SpriteNode : public WorldNode
{
public:
    explicit SpriteNode(const sf::Texture& texture);
    SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect);
    virtual Category::Type getCategory() const;

private:
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    sf::Sprite sprite;
};
