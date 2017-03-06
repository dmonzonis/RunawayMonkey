#include "text_node.h"
#include "utility.h"

#include <cmath>

TextNode::TextNode(const FontHolder& fonts, const std::string& s)
{
    text.setFont(fonts.get(Fonts::Stats));
    text.setCharacterSize(20);
    setString(s);
}

void TextNode::setString(const std::string& s)
{
    text.setString(s);
    centerOrigin(text);
}

Category::Type TextNode::getCategory() const
{
    return Category::Text;
}

void TextNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(text, states);
}
