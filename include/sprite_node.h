#pragma once

#include "world_node.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class SpriteNode : public WorldNode
{
public:
    explicit SpriteNode(const sf::Texture& texture);
    SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect);

private:
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    sf::Sprite sprite;
};
