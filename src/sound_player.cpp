#include "sound_player.h"

const float ListenerZ = 300.f; ///< Height of the sf::Listener over the game's plane.
const float Attenuation = 8.f; ///< Attenuation factor for sounds at a certain distance.

SoundPlayer::SoundPlayer()
    : soundBuffers()
    , sounds()
{
    soundBuffers.load(Sounds::PoopThrow, "resources/woosh.wav");
    soundBuffers.load(Sounds::Chimp, "resources/chimp.wav");
}

void SoundPlayer::play(Sounds::ID id)
{
    play(id, getListenerPosition());
}

void SoundPlayer::play(Sounds::ID id, sf::Vector2f position)
{
    sounds.push_back(sf::Sound());

    sf::Sound& sound = sounds.back();
    sound.setBuffer(soundBuffers.get(id));
    sound.setPosition(position.x, -position.y, 0.f);
    sound.setAttenuation(Attenuation);

    sound.play();
}

void SoundPlayer::cleanUp()
{
    //We use list's remove_if to remove sounds that have ended
    sounds.remove_if([] (const sf::Sound& s)
    {
        return s.getStatus() == sf::Sound::Stopped;
    });
}

sf::Vector2f SoundPlayer::getListenerPosition() const
{
    sf::Vector3f position = sf::Listener::getPosition();
    return sf::Vector2f(position.x, -position.y);
}

void SoundPlayer::setListenerPosition(sf::Vector2f position)
{
    sf::Listener::setPosition(position.x, -position.y, ListenerZ);
}
