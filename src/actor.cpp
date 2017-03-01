#include "actor.h"
#include "utility.h"

Actor::Actor(Type actorType, const TextureHolder& textures)
    : sprite()
    , type(actorType)
{
    switch(actorType)
    {
    case Type::Monkey:
        sprite.setTexture(textures.get(Textures::Monkey));
        break;
    case Type::Businessman:
        sprite.setTexture(textures.get(Textures::Businessman));
        break;
    default:
        //No texture
        break;
    }
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

void Actor::updateCurrent(sf::Time dt, sf::Vector2f playerPos)
{
    if (type != Type::Monkey)
    {
        //Move towards player
        //TODO: path finding AI
        velocity = getSpeed() * unitVector(playerPos - getPosition());
		flip(playerPos);
    }
    move(velocity * dt.asSeconds());
}
