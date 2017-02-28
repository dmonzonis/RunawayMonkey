#include "game.h"

Game::Game()
    : window(sf::VideoMode(800, 600), "Runaway Monkey",
             sf::Style::Titlebar | sf::Style::Close)
    , world(window)
{
    //Implicitly use sf::Time::sleep to maintain 60 FPS
    //TODO: Use more reliable method
    window.setFramerateLimit(60);
}

/*
 * Runs the game loop
 */
void Game::run()
{
    sf::Clock clock;
    while (window.isOpen())
    {
		//deltaTime = time since the last tick
        sf::Time deltaTime = clock.restart();
        processEvents();
        update(deltaTime);
        render();
    }
}

/*
 * Handle user input
 */
void Game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::KeyPressed:
            handleKeyInput(event.key.code, true);
            break;
        case sf::Event::KeyReleased:
            handleKeyInput(event.key.code, false);
            break;
        case sf::Event::Closed:
            window.close();
            break;
        default:
            break;
        }
    }
}

/*
 * Handle key pressed/released input
 */
void Game::handleKeyInput(sf::Keyboard::Key key, bool isPressed)
{
	//Pass it to the World method
    if(!world.handleKeyInput(key, isPressed))
        window.close();
}

/*
 * Update the game logic, using deltaTime to make it FPS independent
 */
void Game::update(sf::Time deltaTime)
{
    world.update(deltaTime);
}

/*
 * Draw everything to buffer and display it on the window
 */
void Game::render()
{
    window.clear();
    world.draw();
    window.display();
}

int main()
{
    Game game;
    game.run();
    return 0;
}
