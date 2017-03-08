#include "text_node.h"
#include "utility.h"

#include <cmath>

TextNode::TextNode(const FontHolder& fonts, const std::string& text)
{
    this->text.setFont(fonts.get(Fonts::Stats));
    this->text.setCharacterSize(20);
    setText(text);
}

void TextNode::setText(const std::string& text)
{
    this->text.setString(text);
    centerOrigin(this->text);
}

Category::Type TextNode::getCategory() const
{
    return Category::Text;
}

void TextNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(text, states);
}
