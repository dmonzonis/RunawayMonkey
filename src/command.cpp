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

void FollowActor::operator() (WorldNode& node, sf::Time) const
{
    Actor& actor = static_cast<Actor&>(node);
    //Set direction towards player
    actor.setVelocity(adjustVectorLength(actorPos - actor.getPosition(), actor.getSpeed()));
    actor.flip(actorPos);
}

void MoveActor::operator() (WorldNode& node, sf::Time) const
{
    Actor& actor = static_cast<Actor&>(node);
    //accelerate the actor
    actor.setVelocity(adjustVectorLength(actor.getVelocity() + velocity, actor.getSpeed()));
}
