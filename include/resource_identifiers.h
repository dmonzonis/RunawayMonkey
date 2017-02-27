#pragma once

#include <SFML/Graphics/Texture.hpp>

namespace Textures
{
enum ID
{
    Monkey,
    Poop,
};
}

//Forward declare ResourceHolder and define types
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;

