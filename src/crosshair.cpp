#include "crosshair.h"

#include <iostream>

Crosshair::Crosshair(const TextureHolder& textures, sf::RenderWindow& w)
    : sprite(textures.get(Textures::Crosshair))
    , window(w)
{
    sf::FloatRect hitbox = sprite.getLocalBounds();
    sprite.setOrigin(hitbox.width / 2.f, hitbox.height / 2.f);
}

void Crosshair::update()
{
    sf::Vector2f pos;
    //Get mouse position in the window
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    //Convert position to world coordinates
    pos = window.mapPixelToCoords(mousePos);
    setPosition(pos);
}

void Crosshair::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}
