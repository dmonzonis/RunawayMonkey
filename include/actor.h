#pragma once

#include "command_queue.h"
#include "projectile.h"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <memory>

class Actor : public Entity
{
public:
    enum Type
    {
        None,
        Monkey,
        Snatcher,
    };

public:
    explicit Actor(Type, const TextureHolder&);
    virtual Category::Type getCategory() const;
    int getHealth();
    void damage(int);
    void die();
    bool isShooting() const;
    void setShooting(bool);
    bool canShoot() const;
    void shoot(Projectile::Type, CommandQueue*);
    void createProjectile(sf::Vector2f direction, Projectile::Type, CommandQueue*);

private:
    virtual void drawCurrent(sf::RenderTarget&, sf::RenderStates states) const;
    virtual void updateCurrent(sf::Time);

private:
    const TextureHolder &textures;
    Type type;
    int health, maxHealth;
    bool shooting;
    sf::Time shootRate, cooldown;
};
