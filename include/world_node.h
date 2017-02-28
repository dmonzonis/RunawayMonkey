#pragma once

#include "category.h"
#include "command.h"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include <vector>
#include <memory>

class WorldNode : public sf::Transformable, public sf::Drawable, public sf::NonCopyable
{
public:
    typedef std::unique_ptr<WorldNode> Ptr;

public:
    WorldNode();
    void attachChild(Ptr child);
    Ptr detachChild(const WorldNode& node);
    void update(sf::Time, sf::Vector2f);
    sf::Vector2f getWorldPosition() const;
    sf::Transform getWorldTransform() const;
    virtual Category::Type getCategory() const;
    void onCommand(const Command&, sf::Time);

private:
    virtual void updateCurrent(sf::Time dt, sf::Vector2f);
    void updateChildren(sf::Time dt, sf::Vector2f);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    std::vector<Ptr> children;
    WorldNode *parent;
};
