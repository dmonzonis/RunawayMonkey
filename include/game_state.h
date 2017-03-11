/**
 * @file game_state.h
 * @author Daniel Monzonís
 */

#pragma once

#include "state.h"
#include "world.h"
#include "player.h"

/**
 * @brief State where the actual gameplay occurs.
 *
 * The game state is the state containing the core gameplay, where the
 * action occurs. It contains information about the game World and the
 * player.
 *
 * @see State
 * @see World
 */
class GameState : public State
{
public:
    /**
     * Default constructor of the game state. Will initialize the
     * State and initializes the player controller's reference to
     * the player actor in the world.
     *
     * @see State::State
     * @see Player::setActor
     */
    GameState(StateManager& manager, Context context);

    /**
     * Handles player input by calling Player::handleRealTimeInput and
     * updates the world by calling World::update
     *
     * @param dt Time since last frame.
     */
    virtual bool update(sf::Time dt);

    /**
     * Draws the world.
     *
     * @see World::draw
     */
    virtual void draw();

    /**
     * Handles events that have an effect on the game state. First, the
     * player handles the event. If it's an event the player can't handle,
     * it acts accordingly, for example, pushing a menu state when the player
     * presses Escape.
     */
    virtual bool handleEvent(const sf::Event& event);

private:
    World world;
    Player& player;
};
