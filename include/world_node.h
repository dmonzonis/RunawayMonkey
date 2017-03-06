#pragma once

#include "category.h"
#include "command.h"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics.hpp>

#include <vector>
#include <memory>
#include <set>

class WorldNode : public sf::Transformable, public sf::Drawable, public sf::NonCopyable
{
public:
    typedef std::unique_ptr<WorldNode> Ptr;
    typedef std::pair<WorldNode*, WorldNode*> Pair;

public:
    WorldNode();
    void attachChild(Ptr child);
    Ptr detachChild(const WorldNode& node);
    void update(sf::Time);
    sf::Vector2f getWorldPosition() const;
    sf::Transform getWorldTransform() const;
    virtual Category::Type getCategory() const;
    void onCommand(const Command&, sf::Time);
    virtual sf::FloatRect getHitbox() const;
    void checkNodeCollision(WorldNode& node, std::set<Pair>& collisionPairs);
    void checkWorldCollision(WorldNode& root, std::set<Pair>& collisionPairs);
    bool isMarkedForRemoval() const;
    void destroy();
    void cleanUp();

private:
    virtual void updateCurrent(sf::Time dt);
    void updateChildren(sf::Time dt);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;
    void drawHitbox(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    std::vector<Ptr> children;
    WorldNode *parent;
    bool removalFlag;
};

//Checks if the hitboxes for two nodes are intersecting
bool collision(WorldNode&, WorldNode&);
