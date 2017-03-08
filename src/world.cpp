#include "world.h"
#include "utility.h"

#include <sstream>

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
    , commandQueue()
    , spawnPoints()
    , counter(sf::Time::Zero)
    , spawnTime(sf::seconds(1.0f))
{
    //When world is created, load all the textures and build the world
    loadResources();
    buildWorld();

    //Center viewport on player
    worldView.setCenter(spawnPosition);
}

void World::update(sf::Time dt)
{
    //Update player and crosshair
    playerActor->setVelocity(0.f, 0.f);
    crosshair->update();
    playerActor->lookAt(crosshair->getPosition());
    //TODO: Remove the following when a GUI is implemented
    std::ostringstream hp;
    hp << "HP " << playerActor->getHealth() << "/" << 3; //3 is the max health
    playerHp->setText(hp.str());

    while (!commandQueue.isEmpty())
        graph.onCommand(commandQueue.pop(), dt);

    //Move view with player (player is always in the center)
    sf::Vector2f velocity = playerActor->getVelocity();
    worldView.move(velocity.x * dt.asSeconds(),
                   velocity.y * dt.asSeconds());

    //Update enemy behaviour
    commandQueue.push(Command(MoveActorTowards(playerActor->getPosition()),
                              Category::Enemy));

    //Handle all collisions in the scene
    handleCollisions();

    //Destroy all nodes marked for removal
    graph.cleanUp();

    //Update counter and spawn new enemies if we reach spawnTime
    counter += dt;
    if (counter >= spawnTime)
    {
        spawnEnemy();
        counter = sf::Time::Zero;
    }

    //Update the entire graph
    graph.update(dt);
}

void World::draw()
{
    //Draw every node in the graph to the screen
    window.setView(worldView);
    window.draw(graph);
    crosshair->update(); //FIXME: have to update it twice so it doesn't get displaced
    window.draw(*crosshair);
}

void World::loadResources()
{
    textures.load(Textures::None, "resources/no_texture.png");
    textures.load(Textures::Monkey, "resources/monkey.png");
    textures.load(Textures::Poop, "resources/poop.png");
    textures.load(Textures::Crosshair, "resources/crosshair.png");
    textures.load(Textures::Grass, "resources/grass_tile.png");
    textures.load(Textures::Snatcher, "resources/snatcher.png");
    fonts.load(Fonts::Stats, "resources/Jellee-Roman.ttf");
}


CommandQueue& World::getCommandQueue()
{
    return commandQueue;
}


void World::buildWorld()
{
    //Initialize root node
    graph.setRoot();

    //Make tiled background
    sf::Texture& texture = textures.get(Textures::Grass);
    sf::IntRect textureRect(worldBounds);
    texture.setRepeated(true);
    std::unique_ptr<SpriteNode> bgSprite(new SpriteNode(texture, textureRect));
    bgSprite->setPosition(worldBounds.left, worldBounds.top);
    graph.attachChild(std::move(bgSprite));

    //Add crosshair and player
    crosshair = new Crosshair(textures, window);
    std::unique_ptr<Actor> monkey(new Actor(Actor::Type::Monkey, textures));
    playerActor = monkey.get();
    playerActor->setPosition(spawnPosition);
    playerActor->setVelocity(0.f, 0.f);
    graph.attachChild(std::move(monkey));

    //TODO: remove the following when a GUI is implemented
    //Add text to show player hp
    std::unique_ptr<TextNode> hpText(new TextNode(fonts, "HP"));
    hpText->setPosition(0.f, 30.0f);
    playerHp = hpText.get();
    playerActor->attachChild(std::move(hpText));

    //Add enemies
    addEnemies();
    spawnEnemy();
}

void World::addEnemies()
{
    addEnemy(Actor::Type::Snatcher, 200.f, -200.f);
    addEnemy(Actor::Type::Snatcher, -800.f, 540.f);
    addEnemy(Actor::Type::Snatcher, 400.f, 350.f);
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

Actor* World::getPlayer()
{
    return playerActor;
}

void World::handleCollisions()
{
    std::set<WorldNode::Pair> collisionPairs;
    graph.checkWorldCollision(graph, collisionPairs);

    for (WorldNode::Pair colliders : collisionPairs)
    {
        //Player-Enemy interaction
        if (categoryMatch(colliders, Category::Player, Category::Enemy))
        {
            //Damage player
            playerActor->damage(1); //FIXME: damage using enemy's attack
            auto& enemy = static_cast<Actor&>(*colliders.second);
	    //TODO: instead of destroying the enemy, make player invulnerable for a while
            enemy.destroy();
        }

        else if (categoryMatch(colliders, Category::Enemy, Category::Projectile))
        {
            //Damage enemy by the projectile's damage
            auto& enemy = static_cast<Actor&>(*colliders.first);
            auto& projectile = static_cast<Projectile&>(*colliders.second);

            enemy.damage(projectile.getDamage());
            projectile.destroy();
        }
    }
}

bool categoryMatch(WorldNode::Pair& colliders, Category::Type type1, Category::Type type2)
{
    Category::Type colliderType1 = colliders.first->getCategory();
    Category::Type colliderType2 = colliders.second->getCategory();

    //Make sure first pair entry has category type1 and second has type2
    if (type1 == colliderType1 && type2 == colliderType2)
    {
        return true;
    }
    //If they are in an inverse order, swap them
    else if (type1 == colliderType2 && type2 == colliderType1)
    {
        std::swap(colliders.first, colliders.second);
        return true;
    }
    else
    {
        return false;
    }
}
