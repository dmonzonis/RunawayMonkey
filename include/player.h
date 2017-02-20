#pragma once
#include "actor.h"

class Player : public Actor
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
    Player();
    bool handleAction(Action, bool);
    bool handleAction(sf::Keyboard::Key, bool);

private:
    std::map<sf::Keyboard::Key, Action> keyBinding;
};
