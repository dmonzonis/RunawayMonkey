#include "actor.h"

void Actor::setIsMoving(bool moving, Direction dir)
{
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
    for (bool &dir : directions)
        dir = false;
}

/*
 * Load texture from file and set the sprite to use it. Return false
 * if loading failed, true otherwise.
 * TODO: change for use with Resource class
 */
bool Actor::loadTexture(std::string filePath)
{
	if (!texture.loadFromFile(filePath))
		return false;
	sprite.setTexture(texture);
	return true;
}

void Actor::move(sf::Vector2f velocity)
{
    sprite.move(velocity);
}

//Flip sprite horizontally
void Actor::flipSprite()
{
    //XXX: Incomplete
    auto scale = sprite.getScale();
    sprite.setScale(-scale.x, scale.y);
}
