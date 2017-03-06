#pragma once

#include "category.h"
#include "world_node.h"
#include "resource.h"
#include "resource_identifiers.h"

#include <string>

class TextNode : public WorldNode
{
public:
    explicit TextNode(const FontHolder&, const std::string&);
    void setString(const std::string&);
    virtual Category::Type getCategory() const;

private:
    virtual void drawCurrent(sf::RenderTarget&, sf::RenderStates) const;

private:
    sf::Text text;
};
