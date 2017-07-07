#include "state.h"
#include "state_manager.h"

State::Context::Context(sf::RenderWindow &window, TextureHolder &textures,
                        FontHolder &fonts, Player &player)
    : window(&window), textures(&textures), fonts(&fonts), player(&player) {}

State::State(StateManager &manager, Context context)
    : manager(&manager), context(context) {}

void State::pushState(States::ID id) { manager->pushState(id); }

void State::popState() { manager->popState(); }

void State::clearStates() { manager->clearStates(); }

State::Context State::getContext() const { return context; }
