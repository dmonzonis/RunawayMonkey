#include "actor.h"

void Actor::setIsMoving(bool moving, Direction dir)
{
    directions[dir] = moving;
}

bool Actor::isMoving(Direction dir)
{
    return directions[dir];
}

sf::Vector2f Actor::getPosition()
{
    return position;
}

void Actor::setPosition(sf::Vector2f newPosition)
{
    position = newPosition;
}

float Actor::getSpeed()
{
    return speed;
}

void Actor::setSpeed(float _speed)
{
    speed = _speed;
}

void Actor::setOrientation(Direction newOrient)
{
    orientation = newOrient;
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
    position += velocity;
    sprite.setPosition(position);
}

/*
 * Flip actor horizontally
 */
void Actor::flip()
{
    auto scale = sprite.getScale();
    sprite.setScale(-scale.x, scale.y);
    if (orientation == RIGHT)
        orientation = LEFT;
    else
        orientation = RIGHT;
}

/*
 * If target is behind actor, flip sprite horizontally.
 */
void Actor::flip(sf::Vector2f target)
{
    float xval = target.x - position.x;
    if ((xval < 0 && orientation == RIGHT) ||
            (xval > 0 && orientation == LEFT))
    {
        flip();
    }
}
