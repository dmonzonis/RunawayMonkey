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
    Banana,
    Healkit,
    BananaBox,
    PoopBox,
    Crosshair,
    Grass,
    TitleBackground,
    TextureCount,
};
}

namespace Fonts
{
enum ID
{
    Main,
};
}

namespace Sounds
{
enum ID
{
    PoopThrow,
    PlayerDamaged,
    Powerup,
};
}

//Forward declare ResourceHolder and define types
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;
typedef ResourceHolder<sf::SoundBuffer, Sounds::ID> SoundBufferHolder;

