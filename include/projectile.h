/**
 * @file projectile.h
 * @author Daniel Monzonís
 */

#pragma once

#include "entity.h"

/**
 * @brief Entity with a fixed lifetime that moves at constant velocity.
 *
 * Projectiles are entities that represent objects that are thrown or shot,
 * and once they are shot they move at constant speed and direction.
 * After a certain lifetime, projectiles are destroyed, since they can't travel
 * to infinity (a realistic projectile would lose speed and fall down after
 * a while).
 * Projectiles also deal damage to actors when they collide with them, the
 * amount of damage depents on the type of projectile.
 * When a projectile collides with something, it is destroyed.
 */
class Projectile : public Entity {
 public:
    enum Type {
        None = 0,
        Poop = 1,  /// Default projectile type that the player shoots
        Banana = 2,
    };

 public:
    /**
     * Projectile constructor.
     *
     * @param textures A reference to the TextureHolder to grab textures from.
     * @param type Projectile::Type of the created projectile object.
     */
    Projectile(const TextureHolder &, Type);

    /**
     * @brief Sets the velocity of the projectile.
     *
     * The velocity is computed with the given direction and the speed of the
     * projectile, which depends on the projectile type.
     *
     * @param direction Indicates the direction the projectile will move to.
     * Its norm is not important, since the velocity will be computed using
     * the projectile's speed, so it does not matter if it's a unit vector
     * or if the norm matches a speed.
     */
    void setDirection(sf::Vector2f);

    /**
     * @return The Projectile::Type type initialized in the constructor.
     */
    Type getType() const;

    /**
     * @return Damage dealt by the projectile depending on its type.
     * For Projectile::Type::Poop it's 1.
     * If the projectile has already collided and is to be removed in the
     * next cleanup, it returns 0.
     */
    int getDamage() const;

    /**
     * @return Category::Projectile
     */
    virtual Category::Type getCategory() const;

 private:
    virtual void updateCurrent(sf::Time);
    virtual void drawCurrent(sf::RenderTarget &, sf::RenderStates states) const;

 protected:
    Type type;
    int damage;
    sf::Time counter, lifetime;
};
