#pragma once

#include "world.h"

#include <SFML/Window/Event.hpp>

class Game : private sf::NonCopyable
{
public:
    Game();
    void run();

private:
    void processEvents();
    void handleKeyInput(sf::Keyboard::Key key, bool isPressed);
    void handleMouseInput(sf::Event::MouseButtonEvent mouse, bool isPressed);
    void update(sf::Time deltaTime);
    void render();

private:
    sf::RenderWindow window;
    World world;
    //sf::CircleShape crosshair;
    //sf::Vector2f crosshairCoord;
};
