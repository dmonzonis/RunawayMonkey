#include "projectile.h"
#include "utility.h"

const float poopSpeed = 500.0f,
            bananaSpeed = 50.0f;

Projectile::Projectile(const TextureHolder& textures, Type type)
    : type(type)
    , damage(1)
    , counter(sf::Time::Zero)
    , lifetime(sf::seconds(3.0f))
{
    sprite.setTexture(textures.get(Textures::Poop));

    switch (type)
    {
    case Poop:
        setSpeed(poopSpeed);
        break;
    case Banana:
        setSpeed(bananaSpeed);
        break;
    default:
        setSpeed(poopSpeed);
        break;
    }

    centerOrigin(sprite);
}

void Projectile::setDirection(sf::Vector2f direction)
{
    velocity = unitVector(direction) * getSpeed();
}

Projectile::Type Projectile::getType() const
{
    return type;
}

int Projectile::getDamage() const
{
    if (isMarkedForRemoval())
        return 0;
    else
        return damage;
}

Category::Type Projectile::getCategory() const
{
    return Category::Projectile;
}

void Projectile::updateCurrent(sf::Time dt)
{
    counter += dt;
    if (counter >= lifetime)
        destroy();
    else
        move(velocity * dt.asSeconds());
}

void Projectile::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}
