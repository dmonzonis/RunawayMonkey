#pragma once

#include "resource.h"
#include "resource_identifiers.h"
#include "world_node.h"
#include "sprite_node.h"
#include "text_node.h"
#include "actor.h"
#include "crosshair.h"
#include "command_queue.h"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <vector>

class World : private sf::NonCopyable
{
public:
    explicit World(sf::RenderWindow&);
    void update(sf::Time);
    void draw();
    CommandQueue& getCommandQueue();
    Actor* getPlayer();

private:
    void loadResources();
    void buildWorld();
    void addEnemies();
    void addEnemy(Actor::Type, float, float);
    void spawnEnemy();

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
};
