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
    void move(sf::Vector2f);
    void flipSprite();
	sf::Sprite sprite;

protected:
    //sf::Sprite sprite;
    sf::Texture texture;
    float speed;
    bool directions[4];
};
