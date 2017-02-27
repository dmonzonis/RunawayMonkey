#pragma once

#include "world_node.h"
#include "resource.h"
#include "resource_identifiers.h"

#include <SFML/Graphics/Sprite.hpp>


typedef enum
{
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3,
} Direction;

class Entity : public WorldNode
{
public:
    float getSpeed() const;
    void setSpeed(float s);
    sf::Vector2f getVelocity() const;
    void setVelocity(sf::Vector2f);
    void setVelocity(float vx, float vy);
    void stop();
    void setOrientation(Direction);
    void flip();
    void flip(sf::Vector2f);

private:
    virtual void updateCurrent(sf::Time deltaTime);

private:
    TextureHolder texture;
    sf::Vector2f position, velocity;
    float speed;
    Direction orientation;

protected:
    sf::Sprite sprite;
    bool directions[4];
};
