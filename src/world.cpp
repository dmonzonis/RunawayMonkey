#include "world.h"
#include "utility.h"

#include <string>

World::World(sf::RenderWindow& w)
    : window(w)
    , worldView(window.getDefaultView())
    , textures()
    , soundPlayer()
    , graph()
    , worldBounds(0.f, 0.f, 2000.f, 2000.f) //FIXME
    , playerActor(nullptr)
    , crosshair(nullptr)
    , spawnPosition(worldBounds.width / 2.f, worldBounds.height / 2.f)
    , commandQueue()
    , enemySpawnPoints()
    , pickupSpawnPoints()
    , counter(sf::Time::Zero)
    , spawnTime(sf::seconds(1.0f))
    , scoreCounter(nullptr)
    , score(0)
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

    //Update score counter (has to be done before any collision handling to avoid
    //being destroyed)
    scoreCounter->setText("Score: " + std::to_string(score));

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
        spawn<Actor>(enemySpawnPoints, false);
        counter = sf::Time::Zero;
    }

    //Update the sound player
    updateSound();

    //Update the entire graph
    graph.update(dt);
}

CommandQueue& World::getCommandQueue()
{
    return commandQueue;
}

Actor* World::getPlayer()
{
    return playerActor;
}

void World::draw()
{
    //Draw every node in the graph to the screen
    window.setView(worldView);
    window.draw(graph);
    crosshair->update(); //FIXME: have to update it twice so it doesn't get displaced
    window.draw(*crosshair);
}

//Loads all textures and fonts
void World::loadResources()
{
    textures.load(Textures::None, "resources/no_texture.png");
    textures.load(Textures::Monkey, "resources/monkey.png");
    textures.load(Textures::Poop, "resources/poop.png");
    textures.load(Textures::Crosshair, "resources/crosshair.png");
    textures.load(Textures::Grass, "resources/grass_tile.png");
    textures.load(Textures::Snatcher, "resources/snatcher.png");
    textures.load(Textures::Dog, "resources/rottweiler.png");
    textures.load(Textures::Healkit, "resources/healkit.png");
    textures.load(Textures::Heart, "resources/heart.png");
    fonts.load(Fonts::Main, "resources/Jellee-Roman.ttf"); //FIXME: readding fonts already in context
}

//Appends all the needed stuff to the root node of the world (player actor, crosshair...)
//and generates the spawn points
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
    playerActor->setSpeed(250.f);
    playerActor->setVelocity(0.f, 0.f);
    graph.attachChild(std::move(monkey));

    //Add the world's sound node
    std::unique_ptr<SoundNode> soundNode(new SoundNode(soundPlayer));
    graph.attachChild(std::move(soundNode));

    /*
    //Add hearts showing player HP
    sf::Texture& heartTexture = textures.get(Textures::Heart);
    std::unique_ptr<SpriteNode> hp1(new SpriteNode(heartTexture));
    hp1->setPosition(-worldView.getSize().x / 2.f + 10.f,
        -worldView.getSize().y / 2.f + 10.f);
    std::unique_ptr<SpriteNode> hp2(new SpriteNode(heartTexture));
    hp2->setPosition(hp1->getPosition().x + 30.f, hp1->getPosition().y);
    std::unique_ptr<SpriteNode> hp3(new SpriteNode(heartTexture));
    hp3->setPosition(hp2->getPosition().x + 30.f, hp2->getPosition().y);
    playerActor->attachChild(std::move(hp1));
    playerActor->attachChild(std::move(hp2));
    playerActor->attachChild(std::move(hp3));
    */

    //Add score counter
    std::unique_ptr<TextNode> scoreText(new TextNode(fonts, "Score: 0"));
    scoreText->setPosition(-worldView.getSize().x / 2.f + 60.f,
                           -worldView.getSize().y / 2.f + 20.f);
    scoreCounter = scoreText.get();
    playerActor->attachChild(std::move(scoreText));


    //Add enemies and pickups
    initializeSpawnPoints();
    //Spawn a couple of pickups and one enemy
    spawn<Actor>(enemySpawnPoints, false);
    spawn<Pickup>(pickupSpawnPoints, true);
    spawn<Pickup>(pickupSpawnPoints, true);
}

//Updates the listener position to be at the player actor's position and cleans up sounds
void World::updateSound()
{
    soundPlayer.setListenerPosition(playerActor->getWorldPosition());
    soundPlayer.cleanUp();
}

//Adds all the initial spawn points for enemies and pickups in the world
void World::initializeSpawnPoints()
{
    //Enemies
    addSpawn(Actor::Type::Snatcher, 200.f, -200.f);
    addSpawn(Actor::Type::Snatcher, -800.f, 540.f);
    addSpawn(Actor::Type::Snatcher, 400.f, 350.f);

    addSpawn(Actor::Type::Dog, 750.f, 1000.f);
    addSpawn(Actor::Type::Dog, -400.f, -1000.f);

    //Pickups
    addSpawn(Pickup::Type::Healkit, 100, -400);
    addSpawn(Pickup::Type::Healkit, -300, 100);
    addSpawn(Pickup::Type::Healkit, 950, 850);
}

//Adds an enemy spawn point at a certain position in the world
void World::addSpawn(Actor::Type type, float x, float y)
{
    SpawnPoint<Actor::Type> sp(type, spawnPosition.x + x, spawnPosition.y + y);
    enemySpawnPoints.push_back(sp);
}

//Adds a pickup spawn point at a certain position in the world
void World::addSpawn(Pickup::Type type, float x, float y)
{
    SpawnPoint<Pickup::Type> sp(type, spawnPosition.x + x, spawnPosition.y + y);
    pickupSpawnPoints.push_back(sp);
}

//Checks for collisions in the world, and then for each pair of colliding objects it
//produces the appropiate interaction
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
            //Play monkey damage sound
            playerActor->playSound(Sounds::PlayerDamaged, &commandQueue);
            //TODO: instead of destroying the enemy, make player invulnerable for a while
            enemy.destroy();
        }

        //Projectile-Enemy interaction
        else if (categoryMatch(colliders, Category::Enemy, Category::Projectile))
        {
            //Damage enemy by the projectile's damage
            auto& enemy = static_cast<Actor&>(*colliders.first);
            auto& projectile = static_cast<Projectile&>(*colliders.second);

            score += enemy.damage(projectile.getDamage());
            projectile.destroy();
        }

        //Player-Pickup interaction
        if (categoryMatch(colliders, Category::Player, Category::Pickup))
        {
            auto& player = static_cast<Actor&>(*colliders.first);
            auto& pickup = static_cast<Pickup&>(*colliders.second);
            //Apply pickup to the player
            pickup.apply(player);
            //Play powerup sound
            playerActor->playSound(Sounds::Powerup, &commandQueue);
            //Destroy pickup
            pickup.destroy();
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
