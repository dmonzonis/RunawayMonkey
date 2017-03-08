/**
 * @file pickup.h
 * @author Daniel Monzonís
 */
#pragma once

#include "actor.h"

class Pickup : public Entity
{
public:
    /**
     * Pickup type will determine the effect of the
     * @ref apply method.
     */
    enum Type
    {
	Healkit, ///Heals the player by 1 health point
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
