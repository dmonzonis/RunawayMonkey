#pragma once

#include "world.h"
#include "player.h"

#include <SFML/Window/Event.hpp>

class Game : private sf::NonCopyable
{
public:
    Game();
    void run();

private:
    void processInput();
    void update(sf::Time deltaTime);
    void render();

private:
    sf::RenderWindow window;
    World world;
    Player player;
    bool paused;
};
