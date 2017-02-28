#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <random>
#include <cmath>
#include <ctime>

const double PI = 3.14159265358979;

void centerOrigin(sf::Sprite&);
void centerOrigin(sf::Text&);
float toDegree(float rad);
float toRadian(float deg);
int randomInt(int exclusiveMax);
