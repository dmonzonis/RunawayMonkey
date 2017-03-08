/**
 * @file utility.h
 * @brief Defines some useful utility functions for general use.
 * @author Daniel Monzonís
 */

#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <random>
#include <cmath>
#include <ctime>
#include <cassert>

const double PI = 3.14159265358979;

/**
 * Sets the origin of the sprite to its center. The origin is the reference
 * point used in most Transform operations like rotate and scale.
 *
 * @param sprite Reference to the sprite that is to be centered. When the
 * function finishes, its origin will have changed to be at the center.
 */
void centerOrigin(sf::Sprite&);

/**
 * Sets the origin of the text object to its center. The origin is the reference
 * point used in most Transform operations like rotate and scale.
 *
 * @param sprite Reference to the text that is to be centered. When the
 * function finishes, its origin will have changed to be at the center.
 */
void centerOrigin(sf::Text&);

/**
 * Changes the angle units from radians to degrees.
 *
 * @param rad Angle in radians.
 *
 * @return The same input angle but in degrees.
 */
float toDegree(float rad);

/**
 * Changes the angle units from degrees to radians.
 *
 * @param deg Angle in degrees.
 *
 * @return The same input angle but in radians.
 */
float toRadian(float deg);

/**
 * Returns a pseudo-random integer from 0 (included) to the integer
 * passed in the argument (excluded). The random seed should be initialized
 * when the program starts, at Game::run().
 *
 * @param exclusiveMax Maximum integer to produce the random number from. The random
 * integer will be in the interval [0, exclusiveMax), so exclusiveMax should be greater
 * than zero.
 *
 * @return A random integer in the interval [0, exclusiveMax).
 */
int randomInt(int exclusiveMax);

/**
 * Computes the euclidean norm of a vector.
 * 
 * @param vec 2-dimensional vector to compute the norm from.
 *
 * @return A float approximation of the euclidean norm of the input vector, that is,
 * it's "length" in the euclidean metric space.
 */
float norm(sf::Vector2f);

/**
 * Returns a unit vector with the same direction of the input vector as an r-value.
 *
 * @param vec Vector to compute the unit vector from.
 *
 * @return A unit vector (that is, a vector with norm equal to 1) with the same direction
 * as the input vector. In other words, a normalized version of the input vector.
 */
sf::Vector2f unitVector(sf::Vector2f);

/**
 * Returns a vector with the same direction as the input vector with the specified length.
 *
 * @param vec Input vector to get the direction from.
 * @param length Length the result vector should have.
 *
 * @return Vector with the same direction as the input vector, but its length will be
 * equal to the length passed as argument.
 */
sf::Vector2f adjustVectorLength(sf::Vector2f, float);
