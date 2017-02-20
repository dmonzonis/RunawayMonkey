#include "entity.h"

class Projectile : public Entity
{
public:
    enum Type
    {
        Poop,
        Banana,
    };
    Projectile(Type);
    void acquireTarget(sf::Vector2f);
    Type getType() const;
    int getDamage() const;

protected:
    Type type;
    sf::Vector2f movingDirection, target;
    sf::Sprite sprite;
    int damage;
};
