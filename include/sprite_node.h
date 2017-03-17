/**
 * @file sprite_node.h
 * @author Daniel Monzonís
 */

#pragma once

#include "world_node.h"

/**
 * @brief Node with a sprite that doesn't interact with the world.
 *
 * SpriteNode is a WorldNode that holds sprite. It's only supposed to be used for
 * rendering sprites that don't interact with the world, like background tiles.
 */
class SpriteNode : public WorldNode
{
public:
    /**
     * Constructor that sets the sprite to use a texture from a reference that's
     * passed directly to it.
     *
     * @param texture Reference to the texture that the sprite will use.
     * The texture should be grabbed from the TextureHolder using the
     * TextureHolder::get method with the corresponding identifier. For example,
     * we can get a reference to a texture tile with identifier Textures::Grass like so
     * @code
     * sf::Texture& grassTexture = textures.get(Texture::Grass);
     * @endcode
     *
     * @see TextureHolder
     */
    explicit SpriteNode(const sf::Texture& texture);

    /**
     * Constructor that sets the sprite to use a texture from a reference and sets
     * a sprite rectangle. This is especially useful for tiles since we can set it to
     * repeat itself within the rectangle bounds by using the setRepeated method
     * from sf::Texture
     * @code
     * texture.setRepeated(true); //texture will repeat itself within the bounds of the rectangle
     * @endcode
     */
    SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect);

    /**
     * @return Category::Sprite
     */
    virtual Category::Type getCategory() const;

    /**
     * Sets the node's identifier to a certain value to differentiate it from others.
     */
    void setId(int id);

    /**
     * Gets the node's identifier, which is 0 if it has not been previously set.
     *
     * @return The node's identifier.
     */
    int getId() const;

    /**
     * Sets the sprite's texture to the given texture reference.
     */
    void setTexture(const sf::Texture& texture);

private:
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    sf::Sprite sprite;
    int id; //used to differentiate some special sprites from others
};
