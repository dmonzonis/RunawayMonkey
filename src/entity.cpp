#include "entity.h"

void Entity::setIsMoving(bool moving, Direction dir)
{
    directions[dir] = moving;
}

bool Entity::isMoving(Direction dir)
{
    return directions[dir];
}

sf::Vector2f Entity::getPosition()
{
    return position;
}

void Entity::setPosition(float x, float y)
{
    position = sf::Vector2f(x, y);
}

void Entity::setPosition(sf::Vector2f newPosition)
{
    position = newPosition;
}

float Entity::getSpeed()
{
    return speed;
}

void Entity::setSpeed(float _speed)
{
    speed = _speed;
}

void Entity::setOrientation(Direction newOrient)
{
    orientation = newOrient;
}


void Entity::stop()
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
bool Entity::loadTexture(std::string filePath)
{
    if (!texture.loadFromFile(filePath))
        return false;
    sprite.setTexture(texture);
    return true;
}

void Entity::move(sf::Vector2f velocity)
{
    position += velocity;
    sprite.setPosition(position);
}

/*
 * Flip actor horizontally
 */
void Entity::flip()
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
void Entity::flip(sf::Vector2f target)
{
    float xval = target.x - position.x;
    if ((xval < 0 && orientation == RIGHT) ||
            (xval > 0 && orientation == LEFT))
    {
        flip();
    }
}
