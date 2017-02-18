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
    float getSpeed();
    void setSpeed(float);
    void stop();
    bool loadTexture(std::string);
    void setTexture();
    void setSpritePosition(float, float);
    void setSpriteScale(float, float);
    sf::Sprite getSprite();
    void move(sf::Vector2f);

protected:
    sf::Sprite sprite;
    sf::Texture texture;
    float speed;
    bool moving;
    bool directions[4];
};
