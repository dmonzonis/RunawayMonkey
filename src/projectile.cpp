#include "projectile.h"

const float poopSpeed = 100.0,
            bananaSpeed = 50.0;

Projectile::Projectile(Type _type)
{
    type = _type;
    switch (type)
    {
    case Poop:
        speed = poopSpeed;
        break;
    case Banana:
        speed = bananaSpeed;
        break;
    }
}

void Projectile::acquireTarget(sf::Vector2f position)
{
    target = position;
}

Projectile::Type Projectile::getType() const
{
    return type;
}

int Projectile::getDamage() const
{
    return damage;
}
