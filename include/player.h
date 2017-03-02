#pragma once

#include "category.h"
#include "command_queue.h"
#include "actor.h"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <map>

class Player
{
public:
    enum Action
    {
	NoAction,
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
    Player();
    bool isShooting() const;
    void setShooting(bool);
    void handleEvent(const sf::Event& event, CommandQueue& commands);
    void handleRealTimeInput(CommandQueue& commands);
    void assignKey(Action, sf::Keyboard::Key);
    sf::Keyboard::Key getAssignedKey(Action) const;
    void update();
    virtual Category::Type getCategory() const;

private:
    static bool isRealTimeAction(Action action);

private:
    bool shooting;
    float speed;
    std::map<sf::Keyboard::Key, Action> keyBinding;
    std::map<Action, Command> actionBinding;
};
