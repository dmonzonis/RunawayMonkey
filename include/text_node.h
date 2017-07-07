/**
 * @file text_node.h
 * @author Daniel Monzonís
 */

#pragma once

#include <string>

#include "category.h"
#include "resource.h"
#include "resource_identifiers.h"
#include "world_node.h"

/**
 * @brief Node with some text that doesn't interact with the world.
 *
 * TextNode is a WorldNode that holds a sf::Text text. It's only supposed to
 * be used for rendering text, as the node doesn't interact with the world in
 * any other way.
 */
class TextNode : public WorldNode {
 public:
    /**
     * Constructor that sets the font of the text to Jelle Roman, which is the
     * only font currently in use. The font should be previously loaded in a
     * FontHolder object.
     *
     * @param fonts FontHolder holding the font resources.
     * @param text String containing the text that the TextNode will contain.
     */
    explicit TextNode(const FontHolder &, const std::string &);

    /**
     * Sets the text to be displayed to the one supplied.
     *
     * @param text Text to be displayed by the TextNode.
     */
    void setText(const std::string &);

    /**
     * @return Category::Text
     */
    virtual Category::Type getCategory() const;

 private:
    virtual void drawCurrent(sf::RenderTarget &, sf::RenderStates) const;

 private:
    sf::Text text;
};
