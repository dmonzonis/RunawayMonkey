#pragma once

#include "world_node.h"
#include "resource.h"
#include "resource_identifiers.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include <string>

class TextNode : public WorldNode
{
public:
    explicit TextNode(const FontHolder&,
                      const std::string&);
    void setString(const std::string&);

private:
    virtual void drawCurrent(sf::RenderTarget&, sf::RenderStates) const;

private:
    sf::Text text;
};
