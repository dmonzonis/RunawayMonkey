/**
 * @file state.h
 * @author Daniel Monzonís
 */
#pragma once

#include "state_identifiers.h"

#include <SFML/System.hpp>

#include <memory>

class State
{
public:
    typedef std::unique_ptr<State> Ptr;

    /**
     * @brief A context shares resources between states.
     */
    struct Context
    {
    };

public:
    State(StateManager& manager, Context context);
    virtual ~State();
    virtual void draw() = 0;
    virtual bool update(sf::Time dt) = 0;
    virtual bool handleEvent(const sf::Event& event) = 0;

protected:
    void addState(States::ID id);
    void popState();
    void clearState();
    Context getContext() const;

private:
    StateManager* manager;
    Context context;
};
