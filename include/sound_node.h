/**
 * @file sound_node.h
 * @author Daniel Monzonís
 */
#pragma once

#include "category.h"
#include "sound_player.h"
#include "world_node.h"

/**
 * @brief Node that can play sound effects using a SoundPlayer.
 *
 * A sound node holds a reference to a SoundPlayer object, and can play sounds
 * at any position in the world (using its parent node as coordinate origin,
 * like all nodes) by using its @ref playSound method.
 *
 * @see SoundPlayer
 */
class SoundNode : public WorldNode {
 public:
    /**
     * Default constructor. Takes a reference to the SoundPlayer to use.
     *
     * @see SoundPlayer
     */
    explicit SoundNode(SoundPlayer &player);

    /**
     * @brief Plays the requested sound at the given position.
     *
     * Forwards the call to the node's player SoundPlayer::play method.
     *
     * @param id Sounds::ID of the sound effect to be played.
     * @param position Position to play the sound at, with the coordinate
     * origin being this node's parent.
     */
    void playSound(Sounds::ID id, sf::Vector2f position);

    /**
     * @return Category::Sound
     */
    virtual Category::Type getCategory() const;

 private:
    SoundPlayer &player;
};
