#include "world.h"

World::World(sf::RenderWindow& w)
    : window(w)
    , worldView(window.getDefaultView())
    , textures()
    , graph()
    , worldBounds(0.f, 0.f, 2000.f, 2000.f) //FIXME
    , spawnPosition(worldBounds.width / 2.f, worldBounds.height / 2.f)
    , player(nullptr)
{
    //When world is created, load all the textures and build the world
    loadTextures();
    buildWorld();

    //Center viewport on player
    worldView.setCenter(spawnPosition);
}

void World::update(sf::Time deltaTime)
{
    //Update player
    player->update();
    sf::Vector2f velocity = player->getVelocity();

    //Move view with player (player is always in the center)
    worldView.move(velocity.x * deltaTime.asSeconds(),
                   velocity.y * deltaTime.asSeconds());

    //Apply movement to the world nodes
    graph.update(deltaTime);
}

void World::draw()
{
    //Draw every node in the graph to the screen
    window.setView(worldView);
    window.draw(graph);
}

void World::loadTextures()
{
    textures.load(Textures::Monkey, "resources/monkey.png");
    textures.load(Textures::Poop, "resources/poop.png");
    textures.load(Textures::Crosshair, "resources/crosshair.png");
    textures.load(Textures::Grass, "resources/grass_tile.png");
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
    std::unique_ptr<Player> monkey(new Player(textures));
    player = monkey.get();
    player->setCrosshair(cross.get());
    player->setPosition(spawnPosition);
    player->setVelocity(0.f, 0.f);
    graph.attachChild(std::move(monkey));
    graph.attachChild(std::move(cross));
}

//0 = close the window, 1 = zoom out, 2 = zoom in
int World::handleKeyInput(sf::Keyboard::Key key, bool isPressed)
{
    //Pass input to Player
    int res = player->handleAction(key, isPressed);
    //FIXME: Debug purposes, remove on release
    switch (res)
    {
    case 2:
        worldView.zoom(1.2);
        break;
    case 3:
        worldView.zoom(0.8);
        break;
    }
    return res;
}

void World::handleMouseInput(sf::Event::MouseButtonEvent mouse, bool isPressed)
{
    auto button = mouse.button;
    switch (button)
    {
    case sf::Mouse::Button::Left:
        player->setShooting(isPressed);
        break;
    default:
        break;
    }
}
