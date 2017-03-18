#include "projectile.h"
#include "utility.h"

const float poopSpeed = 500.0f,
            bananaSpeed = 600.0f;

Projectile::Projectile(const TextureHolder& textures, Type type)
    : type(type)
    , counter(sf::Time::Zero)
{
    switch (type)
    {
    case Poop:
        sprite.setTexture(textures.get(Textures::Poop));
        damage = 1;
        setSpeed(poopSpeed);
        lifetime = sf::seconds(2.0f);
        break;
    case Banana:
        sprite.setTexture(textures.get(Textures::Banana));
        damage = 3;
        setSpeed(bananaSpeed);
        lifetime = sf::seconds(0.5f);
        break;
    default:
        damage = 0;
        setSpeed(poopSpeed);
        lifetime = sf::seconds(3.0f);
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

//Updates the time since it was created, and destroys the projectile if that
//time exceeds the projectile's lifetime. If not, update its position.
void Projectile::updateCurrent(sf::Time dt)
{
    counter += dt;
    if (counter >= lifetime)
    {
        if (type == Banana)
        {
            //TODO: create explosion
        }
        destroy();
    }
    else
        move(velocity * dt.asSeconds());
}

void Projectile::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}
