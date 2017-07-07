#include "sound_node.h"

SoundNode::SoundNode(SoundPlayer &player) : player(player) {}

void SoundNode::playSound(Sounds::ID id, sf::Vector2f position) {
    player.play(id, position);
}

Category::Type SoundNode::getCategory() const { return Category::Sound; }
