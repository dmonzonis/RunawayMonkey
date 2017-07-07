/**
 * @file crosshair.h
 * @author Daniel Monzonís
 */

#pragma once

#include "entity.h"

#include <SFML/Window.hpp>

/**
 * @brief Entity to handle where the player is targeting in the window.
 *
 * Crosshair objects are always positioned where the mouse is pointing to in
 * the render window, and have category Category::Crosshair.
 */
class Crosshair : public Entity {
 public:
    /**
     * @param textures Reference to TextureHolder to grab textures from.
     * @param w Reference to the RenderWindow to get the mouse position from.
     */
    Crosshair(const TextureHolder &, sf::RenderWindow &);

    /**
     * Does nothing, since crosshair objects are updated manually
     * using the Crosshair::update() method.
     */
    virtual void updateCurrent(sf::Time);

    /**
     * Maps the mouse position on the screen and sets the crosshair to that
     * position.
     */
    void update();

    /**
     * @returns Category::Crosshair
     */
    virtual Category::Type getCategory() const;

 private:
    virtual void drawCurrent(sf::RenderTarget &target,
                             sf::RenderStates states) const;

 private:
    sf::RenderWindow &window;
};
