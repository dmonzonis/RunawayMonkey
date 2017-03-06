#pragma once

#include "entity.h"

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class Projectile : public Entity
{
public:
    enum Type
    {
        None = 0,
        Poop = 1,
        Banana = 2,
    };

public:
    Projectile(const TextureHolder&, Type);
    void setDirection(sf::Vector2f);
    Type getType() const;
    int getDamage() const;
    virtual Category::Type getCategory() const;

private:
    virtual void updateCurrent(sf::Time);
    virtual void drawCurrent(sf::RenderTarget&, sf::RenderStates states) const;

protected:
    Type type;
    int damage;
    sf::Time counter, lifetime;
};
