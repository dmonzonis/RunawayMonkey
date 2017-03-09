#include "actor.h"
#include "sound_node.h"
#include "utility.h"

#include <cassert>

Actor::Actor(Type actorType, const TextureHolder& textures)
    : textures(textures)
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

int Actor::getHealth() const
{
    return health;
}

void Actor::setHealth(int health)
{
    this->health = health;
}

void Actor::damage(int amount)
{
    health -= amount;
    if (health <= 0)
    {
        health = 0;
        die();
    }
    else if (health > maxHealth)
    {
        health = maxHealth;
    }
}

void Actor::die()
{
    destroy();
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

void Actor::shoot(Projectile::Type type, CommandQueue* commands)
{
    if (canShoot())
    {
        //Convert type to int because commands don't know about projectiles
        int iType = static_cast<int>(type);
        commands->push(Command(InstanceProjectile(getWorldPosition(), getLookingAt(),
                               iType, textures), Category::SceneRoot));;
	playSound(Sounds::PoopThrow, commands);
        cooldown = sf::Time::Zero;
    }
}

void Actor::playSound(Sounds::ID id, CommandQueue* commands)
{
    sf::Vector2f worldPos = getWorldPosition();
    Command command;
    command.category = Category::Sound;
    command.action = [id, worldPos] (WorldNode& node, sf::Time) 
    {
	SoundNode& soundNode = static_cast<SoundNode&>(node);
	soundNode.playSound(id, worldPos);
    };
    commands->push(command);
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
