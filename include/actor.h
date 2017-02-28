#pragma once

#include "entity.h"

#include <SFML/Graphics/RenderTarget.hpp>

class Actor : public Entity
{
public:
    explicit Actor(const TextureHolder&, Textures::ID);
    void update();
    virtual Category::Type getCategory() const;

private:
    virtual void drawCurrent(sf::RenderTarget&, sf::RenderStates states) const;

private:
    sf::Sprite sprite;
};
