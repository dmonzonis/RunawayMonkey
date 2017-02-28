#include "actor.h"

Actor::Actor(const TextureHolder& textures, Textures::ID id)
    : sprite(textures.get(id))
{
    sf::FloatRect hitbox = sprite.getLocalBounds();
    sprite.setOrigin(hitbox.width / 2.f, hitbox.height / 2.f);
    setSpeed(250.0);
    setOrientation(RIGHT);
    stop();
}

void Actor::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}

Category::Type Actor::getCategory() const
{
    return Category::Player; //FIXME
}
