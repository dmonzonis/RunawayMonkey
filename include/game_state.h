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
 * The game state is the state containing the core gameplay, where you
 * can move around your character, shoot at enemies, and so on.
 */
class GameState : public State
{
public:
    GameState(StateManager& manager, Context context);
    virtual bool update(sf::Time dt);
    virtual void draw();
    virtual bool handleEvent(const sf::Event& event);

private:
    World world;
    Player& player;
};
