#include "game_state.h"

GameState::GameState(StateManager& manager, Context context)
    : State(manager, context)
    , world(*context.window)
    , player(*context.player)
{
    player.setActor(world.getPlayer());
}

bool GameState::update(sf::Time dt)
{
    //Handle player input and update the world
    CommandQueue& commands = world.getCommandQueue();
    player.handleRealTimeInput(commands);
    world.update(dt);
    if(!player.isAlive())
    {
        clearStates();
        pushState(States::Title);
    }
    return true;
}

//Draw everything to buffer and display it on the window
void GameState::draw()
{
    world.draw();
}

bool GameState::handleEvent(const sf::Event& event)
{
    CommandQueue& commands = world.getCommandQueue();
    player.handleEvent(event, commands);
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        pushState(States::Pause);
    return true;
}
