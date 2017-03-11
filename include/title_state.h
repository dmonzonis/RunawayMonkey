/**
 * @file title_state.h
 * @author Daniel Monzonís
 */
#pragma once

#include "state.h"

class TitleState : public State
{
public:
    TitleState(StateManager& manager, Context context);
    virtual bool update(sf::Time dt);
    virtual void draw();
    virtual bool handleEvent(const sf::Event& event);

private:
    sf::Sprite backgroundSprite;
    sf::Text text;
    bool showText;
    sf::Time textEffectTime;
};
