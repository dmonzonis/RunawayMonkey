#include "utility.h"

void centerOrigin(sf::Sprite& sprite)
{
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(std::floor(bounds.left + bounds.width / 2.f),
                     std::floor(bounds.top + bounds.height / 2.f));
}

void centerOrigin(sf::Text& text)
{
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(std::floor(bounds.left + bounds.width / 2.f),
                   std::floor(bounds.top + bounds.height / 2.f));
}

float toDegree(float rad)
{
    return rad * 180.f / PI;
}

float toRadian(float deg)
{
    return deg * PI / 180.f;
}

int randomInt(int exclusiveMax)
{
    return rand() % exclusiveMax;
}
