/**
 * @file sound_player.h
 * @author Daniel Monzonís
 */
#pragma once

#include <list>

#include "resource.h"
#include "resource_identifiers.h"

#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

/**
 * @brief Stores sounds and handles its reproduction and destruction.
 *
 * The class holds a @ref SoundBufferHolder, where all sound buffers are loaded
 * to when the SoundPlayer object is created. When a sound is requested to
 * be played, it makes sure to keep it alive until it ends, and when it
 * finishes playing it destroys it. It also has methods for managing the
 * sf::Listener position and playing sounds at specific locations.
 */
class SoundPlayer : private sf::NonCopyable {
 public:
    /**
     * Default constructor. Loads all the sound buffers from the resources
     * folder (which have .wav format) to the object's memory, mapping them to
     * their corresponding IDs from Sounds::ID.
     */
    SoundPlayer();

    /**
     * Plays the requested sound at the sf::Listener's location on the game
     * plane.
     *
     * @param id ID from Sounds::ID of the sound to be played.
     */
    void play(Sounds::ID id);

    /**
     * Plays the requested sound at the requested position.
     *
     * @param id ID from Sounds::ID of the sound to be played.
     * @param position Position on the game plane to play the sound at.
     */
    void play(Sounds::ID id, sf::Vector2f position);

    /**
     * Removes all sounds that have finished playing from memory.
     */
    void cleanUp();

    /**
     * @return A projection on the game plane of the sf::Listener's position.
     */
    sf::Vector2f getListenerPosition() const;

    /**
     * Sets the sf::Listener's position to the given position, but with the z
     * coordinate being elevated by ListenerZ (see @ref ListenerZ).
     *
     * @param position Projection on the game plane of the new position for the
     * sf::Listener.
     */
    void setListenerPosition(sf::Vector2f position);

 private:
    SoundBufferHolder soundBuffers;
    // Use list since it is faster to remove elements that are in the middle
    std::list<sf::Sound> sounds;
};
