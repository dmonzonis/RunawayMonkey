#pragma once
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

typedef enum
{
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3,
} Direction;

class Actor
{
public:
    void setIsMoving(bool, Direction);
    bool isMoving(Direction);
    sf::Vector2f getPosition();
    void setPosition(sf::Vector2f);
    float getSpeed();
    void setSpeed(float);
    void setOrientation(Direction);
    void stop();
    bool loadTexture(std::string);
    void move(sf::Vector2f);
    void flip();
    void flip(sf::Vector2f);
    sf::Sprite sprite;

protected:
    //sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f position;
    float speed;
    bool directions[4];
    Direction orientation;
};
