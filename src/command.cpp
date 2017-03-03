#include "command.h"
#include "actor.h"
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
    actor.setVelocity(adjustVectorLength(position - actor.getPosition(),
                                         actor.getSpeed()));
    actor.flip(position);
}

void MoveActor::operator() (WorldNode& node, sf::Time) const
{
    Actor& actor = static_cast<Actor&>(node);
    //accelerate the actor
    actor.setVelocity(adjustVectorLength(actor.getVelocity() + velocity,
                                         actor.getSpeed()));
}
