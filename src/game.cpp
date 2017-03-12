#include "game.h"
#include "state_identifiers.h"
#include "title_state.h"
#include "game_state.h"
#include "pause_state.h"
#include "gameover_state.h"
#include "utility.h"

#include <iostream>

Game::Game()
    : window(sf::VideoMode(1000, 800), "Runaway Monkey",
             sf::Style::Titlebar | sf::Style::Close)
    , textures()
    , fonts()
    , player()
    , stateManager(State::Context(window, textures, fonts, player))
    , paused(false)
{
    //Implicitly use sf::Time::sleep to maintain 60 FPS
    //TODO: Use more reliable method
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    textures.load(Textures::TitleBackground, "resources/titlebg.jpg");
    fonts.load(Fonts::Main, "resources/Jellee-Roman.ttf");

    //Register all states and add the titlescreen to the stack
    registerStates();
    stateManager.pushState(States::Title);
}

void Game::run()
{
    sf::Clock clock;
    while (window.isOpen())
    {
        //dt = time since the last tick
        sf::Time dt = clock.restart();
        processInput();
        update(dt);
        //Check if there are no more states left
        if (stateManager.isEmpty())
            window.close();
        render();
    }
}

//Processes events and real-time input
void Game::processInput()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        //Pass the event to player
        stateManager.handleEvent(event);

        //Other actions for events not handled by the player
        if (event.type == sf::Event::Closed)
            window.close();
        else if (event.type == sf::Event::LostFocus)
            paused = true;
        else if (event.type == sf::Event::GainedFocus)
            paused = false;
    }
}

//Update the game logic, using dt to make it FPS independent
void Game::update(sf::Time dt)
{
    if (!paused)
        stateManager.update(dt);
}

//Draw everything to buffer and display it on the window
void Game::render()
{
    //First clear the window
    window.clear();
    //Draw all the states in the stack to buffer
    stateManager.draw();
    //Display buffer
    window.display();
}

void Game::registerStates()
{
    stateManager.registerState<TitleState>(States::Title);
    stateManager.registerState<GameState>(States::Game);
    stateManager.registerState<PauseState>(States::Pause);
    stateManager.registerState<GameOverState>(States::GameOver);
}

int main()
{
    //Set random seed
    srand(time(NULL));

    //Check for errors
    try
    {
        Game game;
        game.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
