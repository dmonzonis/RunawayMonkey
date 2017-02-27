#pragma once

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
    void update(sf::Time deltaTime);
    sf::Vector2f getWorldPosition() const;
    sf::Transform getWorldTransform() const;

private:
    virtual void updateCurrent(sf::Time deltaTime);
    void updateChildren(sf::Time deltaTime);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    std::vector<Ptr> children;
    WorldNode *parent;
};
