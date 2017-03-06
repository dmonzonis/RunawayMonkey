#pragma once

#include "category.h"
#include "command.h"
#include "command_queue.h"
#include "actor.h"

#include <SFML/Window.hpp>

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
        Menu,
        Debug1,
        Debug2,
    };

public:
    Player();
    void handleEvent(const sf::Event& event, CommandQueue& commands);
    void handleRealTimeInput(CommandQueue& commands);
    void assignKey(Action, sf::Keyboard::Key);
    sf::Keyboard::Key getAssignedKey(Action) const;
    void update();
    virtual Category::Type getCategory() const;
    void setActor(Actor*);

private:
    static bool isRealTimeAction(Action action);

private:
    float speed;
    std::map<sf::Keyboard::Key, Action> keyBinding;
    std::map<Action, Command> actionBinding;
    Actor *playerActor;
};
