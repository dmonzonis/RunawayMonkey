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

//Move actor towards given position
struct MoveActorTowards
{
    MoveActorTowards(sf::Vector2f position)
        : position(position)
    {
    }
    void operator() (WorldNode&, sf::Time) const;
    sf::Vector2f position;
};

//Move actor with velocity (vx, vy)
struct MoveActor
{
    MoveActor(float vx, float vy)
        : velocity(vx, vy)
    {
    }
    MoveActor(sf::Vector2f dir)
        : velocity(dir)
    {
    }
    void operator() (WorldNode& node, sf::Time) const;
    sf::Vector2f velocity;
};
