#include "utility.h"

void centerOrigin(sf::Sprite &sprite) {
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(std::floor(bounds.left + bounds.width / 2.f),
                     std::floor(bounds.top + bounds.height / 2.f));
}

void centerOrigin(sf::Text &text) {
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(std::floor(bounds.left + bounds.width / 2.f),
                   std::floor(bounds.top + bounds.height / 2.f));
}

float toDegree(float rad) { return rad * 180.f / PI; }

float toRadian(float deg) { return deg * PI / 180.f; }

int randomInt(int exclusiveMax) { return rand() % exclusiveMax; }

float norm(sf::Vector2f vec) {
    return std::sqrt(vec.x * vec.x + vec.y * vec.y);
}

sf::Vector2f unitVector(sf::Vector2f vec) {
    if (vec == sf::Vector2f(0.f, 0.f))
        return vec;
    return vec / norm(vec);
}

sf::Vector2f adjustVectorLength(sf::Vector2f vec, float length) {
    return length * unitVector(vec);
}
