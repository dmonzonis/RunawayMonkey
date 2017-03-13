#include "pickup.h"

Pickup::Pickup(Type type, const TextureHolder& textures)
    : type(type)
{
    switch (type)
    {
    case Healkit:
        sprite.setTexture(textures.get(Textures::Healkit));
        break;
    case bananaBox:
        sprite.setTexture(textures.get(Textures::BananaBox));
        break;
    case poopBox:
        sprite.setTexture(textures.get(Textures::PoopBox));
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
    case bananaBox:
        player.setShotType(Projectile::Banana);
        break;
    case poopBox:
        player.setShotType(Projectile::Poop);
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
