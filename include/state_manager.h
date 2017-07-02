/**
 * @file state_manager.h
 * @author Daniel Monzonís
 */
#pragma once

#include "state.h"

#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <vector>
#include <map>
#include <cassert>
#include <functional>

/**
 * @brief Manages states from a stack.
 *
 * The manager is a state machine that manages active states in a stack,
 * and has the power to update and render its active states. The manager also handles
 * the events in the program, which will be redirected to its active
 * states.
 *
 * @see State
 */
class StateManager : private sf::NonCopyable
{
public:
    /**
     * Actions that are not done immediately by the manager when
     * requested, but rather stored into a temporary pending changes
     * list, and applied when it is safe to do so.
     *
     * @see applyChanges
     * @see pushState
     * @see popState
     * @see clearStates
     */
    enum Action
    {
        Push,
        Pop,
        Clear,
    };

public:
    /**
     * Default constructor for the state manager. It requires an
     * initial context.
     *
     * @see State::Context
     */
    explicit StateManager(State::Context context);

    /**
     * @brief Takes a state identifier and registers the corresponding state.
     *
     * @param id Identifier of the state to be registered.
     * @tparam T Class for the state to be registered.
     */
    template <typename T>
    void registerState(States::ID id);

    /**
     * Recursively update active states in reverse order (like a stack). If
     * any of the states requests not to update lower states, the function
     * will stop at that state.
     *
     * @param dt Time passed since the last frame.
     */
    void update(sf::Time dt);

    /**
     * Draw every active state to render itself, from the bottom
     * to the top of the stack (that is, in the order they were added
     * to the manager).
     */
    void draw();

    /**
     * @brief Gets polled events and redirects them to the active states.
     *
     * States will handle the events in the reverse order they were added
     * into the manager (like a stack). If any of the states requests
     * for the input not to be passed to lower states, the function will
     * terminate at that state.
     *
     * @param event Event to handle. It will be passed to the currently
     * active states.
     */
    void handleEvent(const sf::Event& event);

    /**
     * Requests the manager to push a state into its stack.
     * The state will not be pushed instantly, but added to a
     * list of pending changes and pushed when it is safe to do so.
     *
     * @param id Identifier of the state to be pushed into the stack.
     */
    void pushState(States::ID id);

    /**
    * Requests the manager to pop the top state from its stack.
    * The state will not be popped instantly, but added to a
    * list of pending changes and popped when it is safe to do so.
    */
    void popState();

    /**
     * Removes all states from the stack. The stack will not be cleared
     * instantly, but added to a list of pending changes and cleared when
     * it is safe to do so.
     */
    void clearStates();

    /**
     * @return true if the stack is empty (it has no states), false
     * otherwise.
     */
    bool isEmpty() const;

private:
    State::Ptr createState(States::ID id);
    void applyChanges();

private:
    struct Change
    {
        explicit Change(Action action, States::ID id = States::None);
        Action action;
        States::ID id;
    };

private:
    std::vector<State::Ptr> stateStack;
    std::vector<Change> pendingChanges;
    State::Context context;
    std::map<States::ID, std::function<State::Ptr()>> stateFactory;
};

template <typename T>
void StateManager::registerState(States::ID id)
{
    stateFactory[id] = [this] ()
    {
        return State::Ptr(new T(*this, context));
    };
}
