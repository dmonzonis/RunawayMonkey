#pragma once

#include "entity.h"

#include <SFML/Graphics/RenderTarget.hpp>

class Actor : public Entity
{
public:
    enum Type
    {
        None,
        Monkey,
        Businessman,
    };

public:
    explicit Actor(Type, const TextureHolder&);
    virtual Category::Type getCategory() const;

private:
    virtual void drawCurrent(sf::RenderTarget&, sf::RenderStates states) const;
    virtual void updateCurrent(sf::Time, sf::Vector2f);

private:
    sf::Sprite sprite;
    Type type;
    int hp, maxHp;
};
