/**
 * @file player.h
 * @author Daniel Monzonís
 */

#pragma once

#include "category.h"
#include "command.h"
#include "command_queue.h"
#include "actor.h"

#include <SFML/Window.hpp>

#include <map>

/**
 * @brief Handles the input issued by the player.
 *
 * Player is a controller class which handles input issued by
 * the player and acts accordingly, be it keyboard input or mouse input.
 * It holds a pointer to the player actor in the world which is
 * assigned when the world is created, so it can access its position and
 * other relevant variables. It also holds a map that maps keyboard keys
 * to an Player::Action, and one that maps each Player::Action to a Command.
 *
 * @see Command
 */
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
        Debug1,
        Debug2,
    };

public:
    /**
     * Default constructor. It will initialize the speed at which the
     * player actor can move, and the default key and action bindings.
     */
    Player();

    /**
     * @brief Handles events when they occur, not in real time.
     *
     * All events that are not normal movement or shooting are handled here
     * and mapped to an action.
     *
     * @param event The event to be handled.
     * @param commands Reference to the world's command queue to push the
     * corresponding Command into.
     *
     * @see MoveActor
     */
    void handleEvent(const sf::Event& event, CommandQueue& commands);

    /**
     * @brief Handles real time input.
     *
     * Handles all input that requires a continuous checking.
     * Real time inputs are movement and shooting.
     * If the player is pressing any of the keys associated with
     * a movement action, it will push a MoveActor command to the
     * command queue with the direction corresponding to the direction of the
     * movement action.
     * If the player is issuing a shoot action (left mouse click by default),
     * the Actor::shoot method will be called on the player actor with
     * Projectile::Type::Poop.
     *
     * @param commands Reference to the world's command queue.
     *
     * @see Actor::shoot
     */
    void handleRealTimeInput(CommandQueue& commands);

    /**
     * @brief Maps a keyboard key to an action.
     *
     * If the key is already mapped to another action, it will replace
     * its old mapping by the new one.
     *
     * @param action Action::Player to be assigned.
     * @param key Keyboard key to be mapped, for example, sf::Keyboard::W.
     */
    void assignKey(Action, sf::Keyboard::Key);

    /**
     * @brief Looks for the key that is mapped to the input action.
     *
     * @param action Action from Player::Action to search.
     *
     * @return The key that is mapped to the action argument if found.
     * If not found, returns sf::Keyboard::Unknown.
     */
    sf::Keyboard::Key getAssignedKey(Action) const;

    /**
     * @return Category::Player
     */
    virtual Category::Type getCategory() const;

    /**
     * @brief Assigns a pointer to an existing actor as the player actor.
     * Actions that directly use Actor methods like Actor::shoot in
     * Player::handleRealTimeInput will use this pointer to execute them.
     */
    void setActor(Actor*);

private:
    static bool isRealTimeAction(Action action);

private:
    float speed;
    std::map<sf::Keyboard::Key, Action> keyBinding;
    std::map<Action, Command> actionBinding;
    Actor *playerActor;
};
