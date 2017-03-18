/**
 * @file pickup.h
 * @author Daniel Monzonís
 */
#pragma once

#include "actor.h"

/**
 * @brief Manages objects that can be picked up by the player and its effects.
 *
 * A pickup is an entity that can be picked up by the player by colliding with it
 * in the world, and different pickups will have different effects. For all the
 * different pickups, see @ref Type.
 */
class Pickup : public Entity
{
public:
    /**
     * Pickup type will determine the effect of the
     * @ref apply method.
     */
    enum Type
    {
        Healkit, ///< Heals the player by 1 health point.
        BananaPack, ///< Gives the player some bananas.
    };

public:
    /**
     * Constructor that initializes the pickup's @ref Type and sets
     * its sprite's texture from the TextureHolder depending on its
     * @ref Type.
     *
     * @param type @ref Type of the pickup.
     * @param textures Reference to the TextureHolder to grab the textures from.
     */
    explicit Pickup(Type type, const TextureHolder& textures);

    /**
     * Applies the effect on the player determined by the
     * pickup's @ref Type.
     */
    void apply(Actor& player) const;

    /**
     * @return Category::Pickup
     */
    virtual Category::Type getCategory() const;

private:
    virtual void drawCurrent(sf::RenderTarget&, sf::RenderStates) const;

private:
    Type type;
};
