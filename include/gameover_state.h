/**
 * @file gameover_state.h
 * @author Daniel Monzonís
 */
#pragma once

#include "state.h"

/**
 * @brief State that shows after the player dies in the game.
 *
 * @see State
 */
class GameOverState : public State
{
public:
    /**
     * Default constructor of the game over state. It initializes the
     * options that will be presented to the player using the resources in
     * the context.
     */
    GameOverState(StateManager& manager, Context context);

    /**
     * Returns true, so states below this one will still update.
     *
     * @see StateManager::update
     */
    virtual bool update(sf::Time dt);

    /**
     * Draws the game over screen to the screen, with the options.
     */
    virtual void draw();

    /**
     * Lets the player move around the options and choose one using
     * the keyboard arrows and return keys.
     */
    virtual bool handleEvent(const sf::Event& event);

    /**
     * Updates the options displayed so that the selected option has
     * a different colour.
     */
    void updateOptionText();

private:
    enum Option
    {
        Retry,
        Quit,
    };

private:
    std::vector<sf::Text> options;
    std::size_t optionIndex;
};
