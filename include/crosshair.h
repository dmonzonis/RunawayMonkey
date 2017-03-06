#pragma once

#include "entity.h"

#include <SFML/Window.hpp>

class Crosshair : public Entity
{
public:
    Crosshair(const TextureHolder&, sf::RenderWindow&);
    virtual void updateCurrent(sf::Time);
    void update();
    virtual Category::Type getCategory() const;

private:
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    sf::Sprite sprite;
    sf::RenderWindow &window;
};
