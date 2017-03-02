#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

namespace Textures
{
enum ID
{
    None,
    Monkey,
    Businessman,
    Poop,
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

//Forward declare ResourceHolder and define types
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;

