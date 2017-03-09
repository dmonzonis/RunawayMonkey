#include "command.h"
#include "actor.h"
#include "projectile.h"
#include "utility.h"

Command::Command()
    : action()
    , category(Category::None)
{
}

Command::Command(Action action, Category::Type type)
    : action(action)
    , category(type)
{
}

void MoveActorTowards::operator() (WorldNode& node, sf::Time) const
{
    Actor& actor = static_cast<Actor&>(node);
    actor.lookAt(position);
    sf::Vector2f moveDir = position - actor.getPosition();
    actor.setVelocity(adjustVectorLength(moveDir, actor.getSpeed()));
}

void MoveActor::operator() (WorldNode& node, sf::Time) const
{
    Actor& actor = static_cast<Actor&>(node);
    //Accelerate the actor, ie update its current velocity
    actor.setVelocity(adjustVectorLength(actor.getVelocity() + velocity,
                                         actor.getSpeed()));
}

void InstanceProjectile::operator() (WorldNode& node, sf::Time) const
{
    assert(direction != sf::Vector2f(0.f, 0.f));
    Projectile::Type projType = static_cast<Projectile::Type>(type);
    assert(projType != Projectile::Type::None);
    //Create the projectile and set its position and direction
    std::unique_ptr<Projectile> proj(new Projectile(textures, projType));
    proj->setPosition(origin);
    proj->setDirection(direction);
    //Attach it to the node that executed the command
    node.attachChild(std::move(proj));
}
