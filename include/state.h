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

class State
{
public:
    typedef std::unique_ptr<State> Ptr;

    /**
     * @brief A context shares resources between states.
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
    State(StateManager& manager, Context context);
    virtual ~State();
    virtual void draw() = 0;
    virtual bool update(sf::Time dt) = 0;
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
