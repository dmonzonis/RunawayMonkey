#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <random>
#include <cmath>
#include <ctime>
#include <cassert>

const double PI = 3.14159265358979;

void centerOrigin(sf::Sprite&);
void centerOrigin(sf::Text&);
float toDegree(float rad);
float toRadian(float deg);
int randomInt(int exclusiveMax);
float norm(sf::Vector2f);
sf::Vector2f unitVector(sf::Vector2f);
sf::Vector2f adjustVectorLength(sf::Vector2f, float);
