#include "game.h"
#include "utility.h"

#include <iostream>

Game::Game()
    : window(sf::VideoMode(1000, 850), "Runaway Monkey",
             sf::Style::Titlebar | sf::Style::Close)
    , world(window)
    , player()
    , paused(false)
{
    //Implicitly use sf::Time::sleep to maintain 60 FPS
    //TODO: Use more reliable method
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);
    //Get player actor reference on the player controller object
    player.setActor(world.getPlayer());
}

void Game::run()
{
    sf::Clock clock;
    while (window.isOpen())
    {
        //dt = time since the last tick
        sf::Time dt = clock.restart();
        processInput();
        //Update the game if it's not on pause
        if (!paused)
            update(dt);
        render();
    }
}

//Processes events and real-time input
void Game::processInput()
{
    CommandQueue& commands = world.getCommandQueue();

    sf::Event event;
    while (window.pollEvent(event))
    {
        //Pass the event to player
        player.handleEvent(event, commands);

        //Other actions for events not handled by the player
        if (event.type == sf::Event::Closed)
            window.close();
        else if (event.type == sf::Event::LostFocus)
            paused = true;
        else if (event.type == sf::Event::GainedFocus)
            paused = false;
    }

    //Lets player handle real-time input
    player.handleRealTimeInput(commands);
}

//Update the game logic, using dt to make it FPS independent
void Game::update(sf::Time dt)
{
    world.update(dt);
}

//Draw everything to buffer and display it on the window
void Game::render()
{
    //First clear the window
    window.clear();
    //Draw everything in the world to buffer
    world.draw();
    //Display buffer
    window.display();
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
