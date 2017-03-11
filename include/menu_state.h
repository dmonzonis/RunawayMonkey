/**
 * @file menu_state.h
 * @author Daniel Monzonís
 */
#pragma once

#include "state.h"

class MenuState : public State
{
public:
    MenuState(StateManager& manager, Context context);
    virtual bool update(sf::Time dt);
    virtual void draw();
    virtual bool handleEvent(const sf::Event& event);
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
