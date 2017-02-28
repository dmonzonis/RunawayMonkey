#include "actor.h"
#include "utility.h"

Actor::Actor(Type actorType, const TextureHolder& textures, Textures::ID id)
    : sprite(textures.get(id))
    , type(actorType)
{
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
