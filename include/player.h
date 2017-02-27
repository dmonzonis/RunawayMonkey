#pragma once

#include "entity.h"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class Player : public Entity
{
public:
    enum Action
    {
        MoveUp = 1,
        MoveLeft = 2,
        MoveDown = 3,
        MoveRight = 4,
        Shoot = 5,
        Menu = 6,
    };

public:
    Player(const TextureHolder&);
    bool handleAction(Action, bool);
    bool handleAction(sf::Keyboard::Key, bool);
    void update();

private:
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    sf::Sprite sprite;
    std::map<sf::Keyboard::Key, Action> keyBinding;
};
