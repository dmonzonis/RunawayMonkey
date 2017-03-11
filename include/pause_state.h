/**
 * @file pause_state.h
 * @author Daniel Monzonís
 */
#pragma once

#include "state.h"

/**
 * @brief State that stops the game and lets the player continue or quit.
 *
 * Accessed by the player during the GameState, it stops its execution and
 * presents the player with a set of options to choose from.
 * The player can choose to resume the game, going back to the game state
 * exactly like he left off, or quit the game, returning back to the
 * title screen.
 *
 * @see State
 */
class PauseState : public State
{
public:
    /**
     * Default constructor of the pause state. It initializes the menu
     * options that will be presented to the player using the resources in
     * the context.
     */
    PauseState(StateManager& manager, Context context);

    /**
     * Returns false, so states below this one won't update.
     *
     * @see StateManager::update
     */
    virtual bool update(sf::Time dt);

    /**
     * Draws the menu options to the screen.
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
        Resume,
        Quit,
    };

private:
    std::vector<sf::Text> options;
    std::size_t optionIndex;
};
