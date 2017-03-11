/**
 * @file title_state.h
 * @author Daniel Monzonís
 */
#pragma once

#include "state.h"

/**
 * @brief State that appears when the game is launched.
 *
 * The title state corresponds to the game's title screen. It is the
 * first state loaded into the state machine when the game launches, and lets
 * the player choose if he wants to play the game.
 *
 * @see State
 */
class TitleState : public State
{
public:
    /**
     * Default constructor for the title state. It grabs the necessary textures
     * and fonts from the context, which are loaded when the game starts.
     */
    TitleState(StateManager& manager, Context context);

    /**
     * Makes the title screen text blink every 0.5 seconds.
     *
     * @param dt Time since the last frame.
     */
    virtual bool update(sf::Time dt);

    /**
     * Draws the title screen on screen.
     */
    virtual void draw();

    /**
     * If the player presses a key, launches the game.
     */
    virtual bool handleEvent(const sf::Event& event);

private:
    sf::Sprite backgroundSprite;
    sf::Text text;
    bool showText;
    sf::Time textEffectTime;
};
