#pragma once

#include "resource.h"
#include "resource_identifiers.h"
#include "world_node.h"
#include "sprite_node.h"
#include "player.h"
#include "crosshair.h"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class World : private sf::NonCopyable
{
public:
    explicit World(sf::RenderWindow& w);
    void update(sf::Time deltaTime);
    void draw();
    int handleKeyInput(sf::Keyboard::Key key, bool isPressed);
	void handleMouseInput(sf::Event::MouseButtonEvent mouse, bool isPressed);

private:
    void loadTextures();
    void buildWorld();

private:
    sf::RenderWindow& window;
    sf::View worldView;
    TextureHolder textures;
    WorldNode graph;
    sf::FloatRect worldBounds;
    sf::Vector2f spawnPosition;
    Player *player;
};
