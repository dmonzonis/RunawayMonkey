/**
 * @file state.h
 * @author Daniel Monzonís
 */
#pragma once

#include "state_identifiers.h"
#include "resource_identifiers.h"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <memory>

//Forward-declarations
class StateManager;
class Player;

/**
 * @brief A state separates different parts of the game with independent functionality.
 *
 * A state is a representation of each well-defined part of the game that has
 * independent functionality from the rest. Examples of states are the Title screen,
 * the Menu, or the Game state, which is where the action takes place.
 * States are managed by the StateManager class, which is nothing more than a state
 * machine, and thus states need to have a reference to that state machine, which is
 * passed in the constructor.
 * Each state has its own methods for input handling, updating its elements and
 * drawing itself to the screen. It communicates with the state manager by requesting
 * the addition or deletion of states from its stack.
 * The state class also holds the @ref Context class, which allows the states to share
 * resources to save memory.
 * @b Note that the State class is not meant to be used as is, but rather used to
 * implement new states as subclasses.
 *
 * @see Context
 * @see StateManager
 * @see TitleState
 * @see MenuState
 * @see GameState
 */
class State
{
public:
    typedef std::unique_ptr<State> Ptr;

    /**
     * @brief A context holds resources to be shared between states.
     *
     * The game's context holds information about the game's window,
     * textures, fonts and the player controller.
     * Textures and fonts loaded into the context will be shared amongst
     * all states.
     */
    struct Context
    {
        Context(sf::RenderWindow& window,
                TextureHolder& textures,
                FontHolder& fonts,
                Player& player);

        sf::RenderWindow* window;
        TextureHolder* textures;
        FontHolder* fonts;
        Player* player;
    };

public:
    /**
     * Default constructor for a state. It requires a reference to its manager
     * (the state machine) and a context.
     *
     * @param manager Reference to the state manager to manage this state.
     * @param context Context to load resources from.
     */
    explicit State(StateManager& manager, Context context);

    /**
     * Draw function with no default implementation. Each subclass of State will
     * have its own implementation.
     */
    virtual void draw() = 0;

    /**
     * Update function with no default implementation. Each subclass of State will
     * have its own implementation.
     */
    virtual bool update(sf::Time dt) = 0;

    /**
     * Event handling function with no default implementation. Each subclass of State will
     * have its own implementation.
     */
    virtual bool handleEvent(const sf::Event& event) = 0;

protected:
    void pushState(States::ID id);
    void popState();
    void clearStates();
    Context getContext() const;

private:
    StateManager* manager;
    Context context;
};
