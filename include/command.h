#pragma once

#include "category.h"

#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

#include <functional>

//Forward-declare WorldNode
class WorldNode;

struct Command
{
    typedef std::function<void(WorldNode&, sf::Time)> Action;
    Command();
    Command(Action, Category::Type);
    Action action;
    Category::Type category;
};

//Move towards actorPos
struct FollowActor
{
    FollowActor(sf::Vector2f actorPos)
        : actorPos(actorPos)
    {
    }
    void operator() (WorldNode&, sf::Time) const;
    sf::Vector2f actorPos;
};

//Move with velocity (vx, vy)
struct MoveActor
{
    MoveActor(float vx, float vy)
        : velocity(vx, vy)
    {
    }
    void operator() (WorldNode& node, sf::Time) const;
    sf::Vector2f velocity;
};
