#include "actor.h"
#include "utility.h"

#include <cassert>

Actor::Actor(Type actorType, const TextureHolder& textures)
    : sprite()
    , type(actorType)
{
    //Cast actor type to texture. For this to work they have to be ordered the same
    Textures::ID actorTexture = static_cast<Textures::ID>(actorType);
    assert(actorTexture < Textures::TextureCount);
    sprite.setTexture(textures.get(actorTexture));
    centerOrigin(sprite);
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
    if (type == Type::Monkey)
        return Category::Player;
    else
        return Category::Enemy;
}

void Actor::updateCurrent(sf::Time dt)
{
    move(velocity * dt.asSeconds());
}
