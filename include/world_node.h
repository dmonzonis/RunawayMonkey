/**
 * @file world_node.h
 * @author Daniel Monzonís
 */

#pragma once

#include "category.h"
#include "command.h"

#include <vector>
#include <memory>
#include <set>

/**
 * @brief A world node is anything that exists and should be updated in the world.
 *
 * A world node (or just node) is something that exists in the world, and is
 * updated and drawn (if it has something to be drawn) each frame. Since it inherits
 * from the sf::Transformable class, it has a position in the world and has methods to
 * change its scale, position or rotation. <br>
 * Nodes get attached to others in a tree structure. Each node has a pointer to its
 * parent node (@c nullptr if the node doesn't have a parent, i.e. it's a root node), and
 * can have several children attached to it using the WorldNode::attachChild method.
 */
class WorldNode : public sf::Transformable, public sf::Drawable, public sf::NonCopyable
{
public:
    typedef std::unique_ptr<WorldNode> Ptr;
    typedef std::pair<WorldNode*, WorldNode*> Pair;

public:
    /**
     * Default node constructor.
     *
     * By default, the node doesn't have a parent and doesn't have any children
     * attached to it, but is not a root node unless you call WorldNode::setRoot().
     */
    WorldNode();

    /**
     * @brief Attaches a node to the calling node as a child.
     *
     * The method will transfer ownership of the node to the calling node. After the
     * function is called, the passed node's parent will be the calling node, and the
     * calling node will have the passed node as a child.
     *
     * @param child WorldNode::Ptr of the node to be attached (passed node).
     */
    void attachChild(Ptr child);

    /**
     * @brief Detaches a child node from the calling node.
     *
     * After the function is called, the calling node will no longer have the passed
     * node as a child, and the passed node will have no parent. Children of the passed
     * node will not be affected by this.
     *
     * @param node Reference to the node to be detached.
     *
     * @return The detached node, now without a parent.
     */
    Ptr detachChild(const WorldNode& node);

    /**
     * @brief Updates the node and then recursively updates its children.
     *
     * By default, nothing happens when a node is updated. More specific nodes,
     * however, override the update function for different purposes. See for
     * example @ref Actor or @ref Projectile.
     */
    void update(sf::Time);

    /**
     * Returns the absolute position in the world, that is, after applying all
     * the transforms relative to its parents up until the root node, that is,
     * until we reach a node without a parent.
     *
     * @return A vector with the absolute position of the node in the world.
     */
    sf::Vector2f getWorldPosition() const;

    /**
     * Returns the resulting transform after applying all the transforms relative
     * to its parents up until the root node, that is, until we reach a node without
     * a parent.
     *
     * @return A transform in the world coordinates.
     */
    sf::Transform getWorldTransform() const;

    /**
     * @return Category::SceneRoot if the node is a root node, Category::Scene
     * otherwise
     *
     * @see WorldNode::setRoot()
     */
    virtual Category::Type getCategory() const;

    /** @brief Sets the node to be a root node.
     *
     * By default, a node is not considered a root node. A node can only become
     * a root node by calling this method. Being or not a root node only affects
     * the node's category (see @ref getCategory()), which affects
     * the logic of the game as some command might need to find the root node
     * (see @ref Command).
     * <b>Important!:</b> Only one node of the node graph should be a root node,
     * which is the node at the top of the tree structure, ultimate parent of all
     * the nodes in play.
     */
    void setRoot();

    /**
     * @brief Reacts to a command and sends it to its children too.
     *
     * The node checks if the command's category matches its category.
     * If it does, it executes it, otherwise it does nothing.
     * In all cases, it sends the command down to its children, calling
     * their own onCommand methods.
     *
     * @see Command
     */
    void onCommand(const Command&, sf::Time);

    /**
     * Returns an empty rectangle. This method is reimplemented in more specific
     * nodes to return the actual hitbox of its sprite.
     *
     * @return An empty rectangle.
     */
    virtual sf::FloatRect getHitbox() const;

    /**
     * Checks if the node is colliding with the passed node (that is, if their
     * hitboxes intersect). If they are colliding, add both nodes as a pair
     * to the collisionPairs set. Then, recursively check its children for
     * collisions with the passed node.
     *
     * @param node Passed node. It's the node to check for collisions with.
     * @param collisionPairs Reference to a set containing pairs of nodes that
     * collide. It is used for collision logic in World::handleCollisions()
     */
    void checkNodeCollision(WorldNode& node, std::set<Pair>& collisionPairs);

    /**
     * Recursively checks collisions for all nodes attached to the passed node.
     *
     * @param root Node that contains all the nodes that should be checked for
     * collisions with each other.
     * @param collisionPairs Reference to a set containing pairs of nodes
     * that collide. It is used for collision logic in World::handleCollisions()
     */
    void checkWorldCollision(WorldNode& root, std::set<Pair>& collisionPairs);

    /**
     * Returns true if the node has been set to be removed the next time the
     * cleanup function is called, and false otherwise.
     *
     * @return True if the node is going to be removed before the next frame, false
     * otherwise.
     *
     * @see destroy()
     * @see cleanUp()
     */
    bool isMarkedForRemoval() const;

    /**
     * Sets the node to be removed the next time the cleanup function is called.
     *
     * @see cleanUp()
     */
    void destroy();

    /**
     * @brief Recursively remove children that are marked for removal.
     *
     * The method will remove any of the calling node's children that is marked for
     * removal (thus detaching them from its parent), and then do the same for
     * the remaining children.
     * After the function finishes, all nodes in the tree below the calling node
     * that were marked for removal will have been removed from the tree.
     *
     * @see destroy()
     */
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
    bool isRoot;
};

/**
 * Checks if the hitboxes for two nodes are intersecting.
 *
 * @return true if the hitboxes intersect, false otherwise.
 */
bool collision(WorldNode&, WorldNode&);
