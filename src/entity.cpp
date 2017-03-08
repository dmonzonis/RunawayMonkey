#include "entity.h"

float Entity::getSpeed() const
{
    return speed;
}

void Entity::setSpeed(float speed)
{
    this->speed = speed;
}

sf::Vector2f Entity::getVelocity() const
{
    return velocity;
}

void Entity::setVelocity(sf::Vector2f velocity)
{
    this->velocity = velocity;
}

void Entity::setVelocity(float vx, float vy)
{
    velocity = sf::Vector2f(vx, vy);
}

void Entity::lookAt(sf::Vector2f point)
{
    lookDirection = point - getWorldPosition();
    flip();
}

sf::Vector2f Entity::getLookingAt()
{
    return lookDirection;
}

void Entity::flip()
{
    //If the actor is looking at something behind it, flip its transform
    if ((lookDirection.x < 0 && orientation == Orientation::Right) ||
            (lookDirection.x > 0 && orientation == Orientation::Left))
    {
        auto scale = getScale();
        //Setting the scale to negative flips the entity about its origin
        setScale(-scale.x, scale.y);
        if (orientation == Orientation::Right)
            orientation = Orientation::Left;
        else
            orientation = Orientation::Right;
    }
}

sf::FloatRect Entity::getHitbox() const
{
    return getWorldTransform().transformRect(sprite.getGlobalBounds());
}

void Entity::updateCurrent(sf::Time dt)
{
    move(velocity * dt.asSeconds());
}

