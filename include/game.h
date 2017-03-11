/**
 * @file game.h
 * @author Daniel Monzonís
 */

#pragma once

#include "resource.h"
#include "resource_identifiers.h"
#include "player.h"
#include "state_manager.h"

/**
 * @brief Class responsible of creating and updating the game loop.
 *
 * Game is the first class created when the game starts, and thus it's what
 * initializes all other necessary classes like World and Player. It also
 * contains the main game loop that will be called after the game is
 * created.
 */
class Game : private sf::NonCopyable
{
public:
    /**
     * Default constructor. It initializes the Render Window (including its
     * size, title and type), the World, and the Player controller.
     */
    Game();

    /**
     * Runs the main game loop, which will update the world by calling
     * World::update unless the game enters a pause state and until
     * the window isn't closed.
     */
    void run();

private:
    void processInput();
    void update(sf::Time deltaTime);
    void render();
    void registerStates();

private:
    sf::RenderWindow window;
    TextureHolder textures;
    FontHolder fonts;
    Player player;
    StateManager stateManager;
    bool paused;
};
