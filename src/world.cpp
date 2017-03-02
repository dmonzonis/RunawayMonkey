#include "world.h"

struct EnemyAI
{
    EnemyAI(sf::Vector2f playerPos)
        : playerPos(playerPos)
    {
    }

    void operator() (WorldNode& node, sf::Time) const
    {
        Actor& actor = static_cast<Actor&>(node);
        //Set direction towards player
        actor.setVelocity(adjustVectorLength(playerPos - actor.getPosition(), actor.getSpeed()));
	actor.flip(playerPos);
    }
    sf::Vector2f playerPos;
};

World::World(sf::RenderWindow& w)
    : window(w)
    , worldView(window.getDefaultView())
    , textures()
    , fonts()
    , graph()
    , worldBounds(0.f, 0.f, 2000.f, 2000.f) //FIXME
    , playerActor(nullptr)
    , crosshair(nullptr)
    , spawnPosition(worldBounds.width / 2.f, worldBounds.height / 2.f)
{
    //When world is created, load all the textures and build the world
    loadResources();
    buildWorld();

    //Center viewport on player
    worldView.setCenter(spawnPosition);
}

void World::update(sf::Time dt)
{
    //Reset player velocity
    playerActor->setVelocity(0.f, 0.f);

    while (!commandQueue.isEmpty())
        graph.onCommand(commandQueue.pop(), dt);

    //Move view with player (player is always in the center)
    sf::Vector2f velocity = playerActor->getVelocity();
    worldView.move(velocity.x * dt.asSeconds(),
                   velocity.y * dt.asSeconds());

    //Place crosshair
    crosshair->update();
    playerActor->flip(crosshair->getPosition());

    //Update AI
    Command enemyAI;
    enemyAI.action = EnemyAI(playerActor->getPosition());
    enemyAI.category = Category::Enemy;
    commandQueue.push(enemyAI);

    //Update the entire graph
    graph.update(dt);
}

void World::draw()
{
    //Draw every node in the graph to the screen
    window.setView(worldView);
    window.draw(graph);
}

void World::loadResources()
{
    textures.load(Textures::None, "resources/no_texture.png");
    textures.load(Textures::Monkey, "resources/monkey.png");
    textures.load(Textures::Poop, "resources/poop.png");
    textures.load(Textures::Crosshair, "resources/crosshair.png");
    textures.load(Textures::Grass, "resources/grass_tile.png");
    textures.load(Textures::Businessman, "resources/businessman.png");
    fonts.load(Fonts::Stats, "resources/Jellee-Roman.ttf");
}


CommandQueue& World::getCommandQueue()
{
    return commandQueue;
}


void World::buildWorld()
{
    //Initialize root node
    WorldNode::Ptr root(new WorldNode());
    graph.attachChild(std::move(root));

    //Make tiled background
    sf::Texture& texture = textures.get(Textures::Grass);
    sf::IntRect textureRect(worldBounds);
    texture.setRepeated(true);
    std::unique_ptr<SpriteNode> bgSprite(new SpriteNode(texture, textureRect));
    bgSprite->setPosition(worldBounds.left, worldBounds.top);
    graph.attachChild(std::move(bgSprite));

    //Add crosshair and player
    std::unique_ptr<Crosshair> cross(new Crosshair(textures, window));
    std::unique_ptr<Actor> monkey(new Actor(Actor::Type::Monkey, textures));
    playerActor = monkey.get();
    crosshair = cross.get();
    playerActor->setPosition(spawnPosition);
    playerActor->setVelocity(0.f, 0.f);
    graph.attachChild(std::move(monkey));
    graph.attachChild(std::move(cross));

    //Add enemies
    addEnemies();
    spawnEnemy();
    spawnEnemy();
}

void World::addEnemies()
{
    addEnemy(Actor::Type::Businessman, 200.f, -200.f);
    addEnemy(Actor::Type::Businessman, -800.f, 540.f);
    addEnemy(Actor::Type::Businessman, 400.f, 350.f);
}

void World::addEnemy(Actor::Type t, float x, float y)
{
    SpawnPoint sp(t, spawnPosition.x + x, spawnPosition.y + y);
    spawnPoints.push_back(sp);
}

void World::spawnEnemy()
{
    if (!spawnPoints.empty())
    {
        //Get a random enemy from the spawn list
        auto size = spawnPoints.size();
        auto it = spawnPoints.begin();
        it += randomInt(size);
        SpawnPoint spawn = *it;

        //Spawn the enemy
        std::unique_ptr<Actor> enemy(new Actor(spawn.type, textures));
        enemy->setPosition(spawn.x, spawn.y);
        enemy->setSpeed(150.f);
        graph.attachChild(std::move(enemy));
    }
}

