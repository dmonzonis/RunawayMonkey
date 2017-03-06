#pragma once

#include "resource.h"
#include "resource_identifiers.h"
#include "world_node.h"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Entity : public WorldNode
{
public:
    float getSpeed() const;
    void setSpeed(float s);
    sf::Vector2f getVelocity() const;
    void setVelocity(sf::Vector2f);
    void setVelocity(float vx, float vy);
    void lookAt(sf::Vector2f);
    sf::Vector2f getLookingAt();
    void flip();
    virtual sf::FloatRect getHitbox() const;

private:
    enum Orientation
    {
	Left,
	Right
    };

private:
    virtual void updateCurrent(sf::Time dt);

private:
    TextureHolder texture;
    sf::Vector2f lookDirection;
    Orientation orientation = Orientation::Right;
    float speed;

protected:
    sf::Sprite sprite;
    sf::Vector2f velocity = sf::Vector2f(0.f, 0.f);
};
