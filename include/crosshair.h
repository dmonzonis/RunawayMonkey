#pragma once

#include "entity.h"

#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Crosshair : public Entity
{
public:
    Crosshair(const TextureHolder&, sf::RenderWindow&);
    void update();

private:
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    sf::Sprite sprite;
    sf::RenderWindow &window;
};
