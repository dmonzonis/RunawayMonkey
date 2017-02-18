#pragma once
#include "player.h"

class Game
{
public:
    Game();
    void run();

private:
    sf::RenderWindow window;
    Player player;
    void processEvents();
    void handleKeyInput(sf::Keyboard::Key, bool);
    void update(sf::Time);
    void render();
};
