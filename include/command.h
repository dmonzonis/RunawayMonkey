#pragma once

#include "category.h"

#include <SFML/System/Time.hpp>

#include <functional>

//Forward-declare WorldNode
class WorldNode;

struct Command
{
    Command();
    std::function<void(WorldNode&, sf::Time)> action;
    Category::Type category;
};
