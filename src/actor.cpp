#include "actor.h"

void Actor::setIsMoving(bool _moving, Direction dir)
{
    moving = _moving;
    directions[dir] = moving;
}

bool Actor::isMoving(Direction dir)
{
    return directions[dir];
}

float Actor::getSpeed()
{
    return speed;
}

void Actor::setSpeed(float _speed)
{
    speed = _speed;
}

void Actor::stop()
{
    //Set all movement directions to false
    directions[UP] = false;
    directions[DOWN] = false;
    directions[LEFT] = false;
    directions[RIGHT] = false;
}

bool Actor::loadTexture(std::string filePath)
{
	return texture.loadFromFile(filePath);
}

void Actor::setTexture()
{
	sprite.setTexture(texture);
}

void Actor::setSpritePosition(float x, float y)
{
	sprite.setPosition(x, y);
}

void Actor::setSpriteScale(float factorX, float factorY)
{
	sprite.setScale(factorX, factorY);
}

sf::Sprite Actor::getSprite()
{
	return sprite;
}

void Actor::move(sf::Vector2f velocity)
{
	sprite.move(velocity);
}
