#include "game.h"

//Initial game settings are loaded in the constructor
Game::Game()
    : window(sf::VideoMode(800, 600), "Runaway Monkey",
             sf::Style::Titlebar | sf::Style::Close)
    , world(window)
{
    window.setFramerateLimit(60);
    //Initialize crosshair
    //FIXME
    //const float r = 20.0;
    //crosshair.setRadius(r);
    //crosshair.setFillColor(sf::Color::Red);
    //crosshair.setOrigin(r, r); //set origin at center
    //crosshairCoord.x = crosshairCoord.y = 0.0;
}

//Runs the game loop
void Game::run()
{
    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Time deltaTime = clock.restart();
        processEvents();
        update(deltaTime);
        render();
    }
}

//Handle user input
void Game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::MouseMoved:
            //FIXME
            //crosshairCoord.x = event.mouseMove.x;
            //crosshairCoord.y = event.mouseMove.y;
            break;
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

//Handle key pressed/released input
void Game::handleKeyInput(sf::Keyboard::Key key, bool isPressed)
{
    if(!world.handleKeyInput(key, isPressed))
        window.close();
}

//Update the game logic, using deltaTime to make it independant from FPS
void Game::update(sf::Time deltaTime)
{
    world.update(deltaTime);

    //Player movement
    /*
    sf::Vector2f movement(0.f, 0.f);

    if (player.isMoving(UP))
        movement.y -= player.getSpeed();
    if (player.isMoving(DOWN))
        movement.y += player.getSpeed();
    if (player.isMoving(LEFT))
        movement.x -= player.getSpeed();
    if (player.isMoving(RIGHT))
        movement.x += player.getSpeed();

    player.move(movement * frameTime.asSeconds());

    //Crosshair placement
    crosshair.setPosition(crosshairCoord.x, crosshairCoord.y);
    player.flip(crosshairCoord);
    */
}

//Draw everything to buffer and display it on the window
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
