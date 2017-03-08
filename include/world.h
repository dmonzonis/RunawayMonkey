/**
 * @file world.h
 * @author Daniel Monzonís
 */

#pragma once

#include "resource.h"
#include "resource_identifiers.h"
#include "world_node.h"
#include "sprite_node.h"
#include "text_node.h"
#include "actor.h"
#include "crosshair.h"
#include "command_queue.h"

#include <SFML/Window.hpp>

#include <vector>

/**
 * @brief Class responsible of holding, updating and drawing all the gameplay elements.
 *
 * World is where all the nodes in play reside. It is also the responsible of updating the
 * game logic and drawing all drawable objects to screen when issued by the Game class.
 * World holds nodes in a tree structure, by having a root WorldNode, which stands on the top
 * of all nodes, and all nodes added to play are appended to it as children or to
 * some previously appended nodes.
 * World updates its nodes starting by the root node, which recursively calls the
 * WorldNode::update method on its children.
 * World also keeps track of the command queue (see CommandQueue), and is the class
 * that pops the commands from the queue in its World::update method and sends them
 * to its root node, which then sends it to its children recursively.
 * World has a pointer to the player actor, which is assigned after it is created.
 * It also keeps track of the spawn points for enemies, and the types of enemies
 * these points will spawn.
 * The world is responsible for handling the logic, as well as the collisions, that
 * occur in the game.
 * World also holds the resource holders with all the necessary resources, which are
 * loaded in the World::loadResources() method.
 */
class World : private sf::NonCopyable
{
public:
    /**
     * @brief Constructor for the world.
     *
     * It initializes the View (see 
     * <a href="https://www.sfml-dev.org/documentation/2.0/classsf_1_1View.php">sf::View</a>),
     * the world bounds (the rectangle that limits the world's playable area),
     * sets the player's spawn position,
     * and the enemy spawn rate.
     * It then loads all the resources using resource holders, and builds the world by
     * attaching all necessary sprite nodes and starting entities (like the player actor
     * and the crosshair).
     * 
     * @param w Reference to the game's RenderWindow.
     *
     * @see ResourceHolder
     */
    explicit World(sf::RenderWindow&);

    /**
     * @brief Updates the logic of the elements in play.
     *
     * It will recursively update all the nodes from the graph, starting from root, calling
     * their respective update functions depending on the node type. It also gets all the
     * commands from the command queue and sends them down the graph, where they will be
     * passed to eventually all the nodes, but only executed by those whose Category::Type
     * matches the command's category.
     * It also handles collisions between entities, acting accordingly depending on
     * the categories of the colliding entities.
     *
     *
     * @param dt Time that has passed since the last time the update function was called.
     * It is used by the game logic to update the game independently of FPS.
     *
     * @see Command
     * @see CommandQueue
     */
    void update(sf::Time);

    /**
     * Draws every node in the graph to the RenderWindow
     */
    void draw();

    /**
     * Returns a reference to the world's command queue.
     * 
     * @return A reference to the world's command queue in its current state.
     *
     * @see CommandQueue
     */
    CommandQueue& getCommandQueue();

    /**
     * Returns a pointer to the playerActor, which is assigned when it is created
     * in the constructor.
     */
    Actor* getPlayer();

private:
    void loadResources();
    void buildWorld();
    void addEnemies();
    void addEnemy(Actor::Type, float, float);
    void spawnEnemy();
    void handleCollisions();

private:
    struct SpawnPoint
    {
        SpawnPoint(Actor::Type type, float x, float y)
            : type (type)
            , x(x)
            , y(y)
        {
        }

        Actor::Type type;
        float x, y;
    };

private:
    sf::RenderWindow& window;
    sf::View worldView;
    TextureHolder textures;
    FontHolder fonts;
    WorldNode graph;
    sf::FloatRect worldBounds;
    Actor *playerActor;
    Crosshair *crosshair;
    sf::Vector2f spawnPosition;
    CommandQueue commandQueue;
    std::vector<SpawnPoint> spawnPoints;
    sf::Time counter, spawnTime;
};

bool categoryMatch(WorldNode::Pair& colliders, Category::Type type1, Category::Type type2);
