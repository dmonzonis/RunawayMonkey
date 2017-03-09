/**
 * @file resource_identifiers.h
 * @author Daniel Monzonís
 */

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace Textures
{
enum ID
{
    /* Actor textures go in here in the same order as Actor category */
    None,
    Monkey,
    Snatcher,
    /* End actor textures */
    Poop,
    Healkit,
    Crosshair,
    Grass,
    TextureCount,
};
}

namespace Fonts
{
enum ID
{
    Stats,
};
}

namespace Sounds
{
enum ID
{
    PoopThrow,
    Chimp,
};
}

//Forward declare ResourceHolder and define types
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;
typedef ResourceHolder<sf::SoundBuffer, Sounds::ID> SoundBufferHolder;

