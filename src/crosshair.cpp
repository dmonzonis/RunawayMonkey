#include "crosshair.h"
#include "utility.h"

Crosshair::Crosshair(const TextureHolder& textures, sf::RenderWindow& w)
    : window(w)
{
    sprite.setTexture(textures.get(Textures::Crosshair));
    sf::FloatRect hitbox = sprite.getLocalBounds();
    sprite.setOrigin(hitbox.width / 2.f, hitbox.height / 2.f);
}

void Crosshair::updateCurrent(sf::Time)
{
    //Do nothing as crosshair is updated manually
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

Category::Type Crosshair::getCategory() const
{
    return Category::Crosshair;
}

void Crosshair::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}

