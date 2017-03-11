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
 * @brief Class responsible of launching the application and updating the
 * game loop.
 *
 * Game is the first class created when the game starts, and thus it's what
 * initializes all other necessary classes like the state manager. It also
 * contains the main game loop that will be called after the game is
 * created.
 */
class Game : private sf::NonCopyable
{
public:
    /**
     * Default constructor. It initializes the Render Window (including its
     * size, title and type), the state manager, and the context's resources.
     */
    Game();

    /**
     * Runs the main game loop, which will update the state manager unless
     * the window is closed or the state manager runs out of states.
     */
    void run();

private:
    void processInput();
    void update(sf::Time dt);
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
