#pragma once

#include "entity.h"
#include "crosshair.h"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class Player : public Entity
{
public:
    enum Action
    {
        MoveUp,
        MoveLeft,
        MoveDown,
        MoveRight,
        Shoot,
        Menu,
        Debug1,
        Debug2,
    };

public:
    Player(const TextureHolder&);
    void setCrosshair(Crosshair*);
    bool isShooting();
    void setShooting(bool);
    int handleAction(Action, bool);
    int handleAction(sf::Keyboard::Key, bool);
    void update();

private:
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    sf::Sprite sprite;
    Crosshair *crosshair;
    bool shooting;
    std::map<sf::Keyboard::Key, Action> keyBinding;
};
