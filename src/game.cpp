#include "game.h"

//Initial game settings are loaded in the constructor
Game::Game()
{
    window.create(sf::VideoMode(800, 600), "Runaway Monkey",
                  sf::Style::Titlebar | sf::Style::Close);
    //Initialize player
    if (!player.loadTexture("resources/monkey.png"))
    {
        //TODO: Handle error
        throw std::runtime_error("Couldn't load texture");
    }
    player.sprite.setPosition(200, 200);
    player.sprite.setOrigin(20, 20);
    player.setSpeed(250.f);
    player.stop();
}

//Runs the game loop
void Game::run()
{
    const sf::Time frameTime = sf::seconds(1.f / 60.f); //set update rate to 60 FPS
    sf::Clock clock;
    sf::Time deltaTime = sf::Time::Zero; //time since last update
    while (window.isOpen())
    {
        processEvents();
        deltaTime += clock.restart();
        //Use a constant time per frame to prevent lag errors (when FPS drop below 60)
        while (deltaTime > frameTime)
        {
            deltaTime -= frameTime;
            processEvents();
            update(frameTime);
        }
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
    switch (key)
    {
    case sf::Keyboard::W:
        player.setIsMoving(isPressed, UP);
        break;
    case sf::Keyboard::A:
        player.setIsMoving(isPressed, LEFT);
        break;
    case sf::Keyboard::S:
        player.setIsMoving(isPressed, DOWN);
        break;
    case sf::Keyboard::D:
        player.setIsMoving(isPressed, RIGHT);
        break;
    case sf::Keyboard::Escape:
        //TODO: make menu
        window.close();
        break;
    case sf::Keyboard::Y:
        //XXX: Debug key, remove for release
        if (isPressed)
            player.flipSprite();
        break;
    default:
        break;
    }
}

//Update the game logic, using deltaTime to make it independant from FPS
void Game::update(sf::Time frameTime)
{
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
}

//Draw everything to buffer and display it on the window
void Game::render()
{
    window.clear();
    window.draw(player.sprite);
    window.display();
}

int main()
{
    Game game;
    game.run();
    return 0;
}
