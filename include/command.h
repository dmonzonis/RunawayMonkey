/**
 * @file command.h
 * @author Daniel Monzonís
 */

#pragma once

#include <functional>
#include <memory>

#include "category.h"
#include "resource.h"
#include "resource_identifiers.h"

#include <SFML/System.hpp>

// Forward-declarations
class WorldNode;
class Actor;
class Projectile;

/**
 * @brief Commands handle actions in an abstract way.
 *
 * Commands have an Action, which is a function that takes a WorldNode reference
 * and a time, and a category, which is a Category::Type indicating which types
 * of nodes should execute the command.
 */
struct Command {
    /**
     * Actions are function pointers that take a reference to a WorldNode and a
     * time.
     */
    typedef std::function<void(WorldNode &, sf::Time)> Action;

    /**
     * Default constructor.
     * Leaves the action empty, and sets category to Category::None
     */
    Command();

    /**
     * Alternative constructor which initializes the action and the category
     * type.
     * @param action Function to be executed, following the Action format.
     * @param type Specifies the nodes that should execute this command when
     * it's passed to them.
     */
    Command(Action action, Category::Type type);

    /**
     * Function to be called when the command is executed.
     */
    Action action;

    /**
     * Type of the nodes that should execute the command.
     */
    Category::Type category;
};

/**
 * @brief Functor to move actor towards a given position.
 *
 * See @ref Functors for more information on what they are and how they are
 * used.
 *
 * The constructor takes a position in the world. The functor
 * will return an action that moves the node towards that position.
 *
 * @see Command
 */
struct MoveActorTowards {
    explicit MoveActorTowards(sf::Vector2f position) : position(position) {}
    void operator()(WorldNode &, sf::Time) const;
    sf::Vector2f position;
};

/**
 * @brief Functor to move an actor a given distance.
 *
 * See @ref Functors for more information on what they are and how they are
 * used.
 *
 * The function returned will move an actor in the world by a certain distance
 * passed in the constructor.
 *
 * @see Command
 */
struct MoveActor {
    /**
     * Gets the distance that the actor will move
     * by its cartesian components in the x and y axis
     * @param vx Distance to move in the x axis.
     * @param vy Distance to move in the y axis.
     */
    MoveActor(float vx, float vy) : velocity(vx, vy) {}

    /**
     * Gets the distance to move directly from a vector.
     * @param v Vector with the distance and direction
     * the actor will move.
     */
    explicit MoveActor(sf::Vector2f v) : velocity(v) {}
    void operator()(WorldNode &node, sf::Time) const;
    sf::Vector2f velocity;
};

/**
 * @brief Functor to create a projectile as a child of a node.
 *
 * See @ref Functors for more information on what they are and how they are
 * used.
 *
 * The function returned will create a projectile of a given type and attach it
 * to the node that executes it as a child.
 *
 * @see Command
 * @see Projectile
 */
struct InstanceProjectile {
    /**
     * InstanceProjectile constructor
     *
     * @param origin Position where the projectile will be
     * instantiated relative to the node.
     * @param direction Direction of the instantiated projectile.
     * @param type Projectile type that will be casted to a
     * Projectile::Type, so the corresponding integer value should be used.
     * @param textures Reference to the TextureHolder for the projectile
     * to grab its texture from depending on its type.
     *
     * @see Projectile
     */
    InstanceProjectile(const sf::Vector2f origin, sf::Vector2f direction,
                       int type, const TextureHolder &textures)
        : origin(origin), direction(direction), type(type), textures(textures) {
    }
    void operator()(WorldNode &node, sf::Time) const;
    const sf::Vector2f origin;
    sf::Vector2f direction;
    int type;
    const TextureHolder &textures;
};

/**
 * @brief Functor to update the player's health in the HUD
 *
 * See @ref Functors for more information on what they are and
 * how they are used.
 *
 * The function returned will update the sprite node if it has identifiers 1, 2
 * or 3 (which are the hearts corresponding to the player's health), to a full
 * heart or an empty heart depending on the player's health.
 *
 * @see Command
 * @see SpriteNode
 */
struct UpdatePlayerHealth {
    /**
     * UpdatePlayerHealth constructor.
     *
     * @param health Current health of the player actor.
     * @param textures Reference to the TextureHolder for the heart sprites to
     * grab their new texture from.
     *
     * @see Actor
     */
    UpdatePlayerHealth(const int health, const TextureHolder &textures)
        : health(health), textures(textures) {}
    void operator()(WorldNode &node, sf::Time) const;
    const int health;
    const TextureHolder &textures;
};
