/**
 * @file category.h
 * @author Daniel Monzonís
 */

#pragma once

namespace Category
{
enum Type
{
    None,
    
    Scene, ///Category for all nodes that don't interact with anything with exception of the root node.
    SceneRoot, ///Category for the world's root node.
    Player,
    Crosshair,
    Enemy,
    Pickup,
    Projectile,
    Text,
};
}
