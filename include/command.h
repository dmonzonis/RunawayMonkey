#pragma once

#include "category.h"

#include <SFML/System/Time.hpp>

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
