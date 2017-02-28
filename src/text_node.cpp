#include "text_node.h"

#include <cmath>

TextNode::TextNode(const FontHolder& fonts, const std::string& s)
{
    text.setFont(fonts.get(Fonts::Stats));
    text.setCharacterSize(20);
    setString(s);
}

void TextNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(text, states);
}

void TextNode::setString(const std::string& s)
{
    text.setString(s);
    //Center origin
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(std::floor(bounds.left + bounds.width / 2.f),
                   std::floor(bounds.top + bounds.height / 2.f));
}
