#include "pickup.h"

Pickup::Pickup(Type type, const TextureHolder& textures)
    : type(type)
{
    switch (type)
    {
    case Healkit:
        sprite.setTexture(textures.get(Textures::Healkit));
        break;
    default:
        sprite.setTexture(textures.get(Textures::None));
        break;
    }
}

void Pickup::apply(Actor& player) const
{
    switch (type)
    {
    case Healkit:
        player.damage(-1);
        break;
    default:
        break;
    }
}

Category::Type Pickup::getCategory() const
{
    return Category::Pickup;
}

void Pickup::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}
