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
}

Category::Type Actor::getCategory() const
{
    if (type == Type::Monkey)
        return Category::Player;
    else
        return Category::Enemy;
}

int Actor::getHealth()
{
    return health;
}

void Actor::damage(int amount)
{
    health -= amount;
    if (health < 0)
        health = 0;
    die();
}

void Actor::die()
{
}

void Actor::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}

void Actor::updateCurrent(sf::Time dt)
{
    move(velocity * dt.asSeconds());
}
