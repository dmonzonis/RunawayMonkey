/**
 * @file entity.h
 * @author Daniel Monzonís
 */

#pragma once

#include "resource.h"
#include "resource_identifiers.h"
#include "world_node.h"

/**
 * @brief WorldNode that has a presence and can move around.
 *
 * Entity objects are nodes that have an orientation and can
 * move around at some given speed. They also have a hitbox
 * representing its bounding rectangle.
 */
class Entity : public WorldNode {
 public:
    /**
     * @return The speed at which the entity can move in the
     * world.
     */
    float getSpeed() const;

    /**
     * Sets the entity's speed to a constant value.
     */
    void setSpeed(float s);

    /**
     * @return The velocity at which the entity is moving in
     * vector form, that is, the distance and direction it is
     * going to move when it updates.
     */
    sf::Vector2f getVelocity() const;

    /**
     * Sets the entity's velocity to a constant value.
     */
    void setVelocity(sf::Vector2f);

    /**
     * Sets the entity's velocity to a constant value.
     */
    void setVelocity(float vx, float vy);

    /**
     * Sets the entity to be looking at a point in the world in the
     * form of a vector, and calls @ref flip() to flip the
     * transform in case the orientation changed.
     *
     * @param point Point in space where the entity will be looking at,
     * in world coordinates.
     */
    void lookAt(sf::Vector2f);

    /**
     * @return The world coordinates of the point the entity is currently
     * looking at.
     */
    sf::Vector2f getLookingAt();

    /**
     * Flips the entity's transform horizontally if its orientation has changed,
     * that is,
     * if it's looking at something that's behind it.
     */
    void flip();

    /**
     * @return A rectangle object corresponding to the entity's hitbox or
     * bounds
     */
    virtual sf::FloatRect getHitbox() const;

 private:
    enum Orientation { Left, Right };

 private:
    virtual void updateCurrent(sf::Time dt);

 private:
    TextureHolder texture;
    sf::Vector2f lookDirection;
    Orientation orientation = Orientation::Right;
    float speed;

 protected:
    sf::Sprite sprite;
    sf::Vector2f velocity = sf::Vector2f(0.f, 0.f);
};
