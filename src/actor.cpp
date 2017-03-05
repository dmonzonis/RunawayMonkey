#include "actor.h"
#include "utility.h"

#include <cassert>

Actor::Actor(Type actorType, const TextureHolder& textures)
    : sprite()
    , textures(textures)
    , type(actorType)
    , health(3)
    , maxHealth(3)
    , shooting(false)
    , shootRate(sf::seconds(0.25f))
    , cooldown(sf::seconds(0.f))
{
    //Cast actor type to texture. For this to work they have to be ordered the same
    Textures::ID actorTexture = static_cast<Textures::ID>(actorType);
    assert(actorTexture < Textures::TextureCount);
    sprite.setTexture(textures.get(actorTexture));
    centerOrigin(sprite);
    setSpeed(250.0);
}

Category::Type Actor::getCategory() const
{
    if (type == Type::Monkey)
        return Category::Player;
    else
        return Category::Enemy;
}

int Actor::getHealth()
{
    return health;
}

void Actor::damage(int amount)
{
    health -= amount;
    if (health < 0)
        health = 0;
    die();
}

void Actor::die()
{
}

bool Actor::isShooting() const
{
    return shooting;
}

void Actor::setShooting(bool flag)
{
    shooting = flag;
}

bool Actor::canShoot() const
{
    return cooldown >= shootRate;
}

void Actor::shoot(Projectile::Type type, CommandQueue *commands)
{
    if (canShoot())
    {
        //Convert type to int because commands don't know about projectiles
        int iType = static_cast<int>(type);
        commands->push(Command(InstanceProjectile(getWorldPosition(), getLookingAt(),
                               iType, textures), Category::Scene));;
	cooldown = sf::Time::Zero;
    }
}

void Actor::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}

void Actor::updateCurrent(sf::Time dt)
{
    move(velocity * dt.asSeconds());
    if (cooldown < shootRate)
        cooldown += dt;
}
