#include "player.h"

Player::Player(const TextureHolder& textures)
    : sprite(textures.get(Textures::Monkey))
    , crosshair(nullptr)
{
    //Initial hardcoded keybindings
    keyBinding[sf::Keyboard::W] = keyBinding[sf::Keyboard::Up] = MoveUp;
    keyBinding[sf::Keyboard::A] = keyBinding[sf::Keyboard::Left] = MoveLeft;
    keyBinding[sf::Keyboard::S] = keyBinding[sf::Keyboard::Down] = MoveDown;
    keyBinding[sf::Keyboard::D] = keyBinding[sf::Keyboard::Right] = MoveRight;
    keyBinding[sf::Keyboard::Escape] = Menu;

    sf::FloatRect hitbox = sprite.getLocalBounds();
    sprite.setOrigin(hitbox.width / 2.f, hitbox.height / 2.f);
    setSpeed(250.0);
    setOrientation(RIGHT);
    stop();
}

void Player::setCrosshair(Crosshair *cross)
{
    crosshair = cross;
}


/*
 * Handle given action. Returns false if game should quit, true otherwise
 */
bool Player::handleAction(Action action, bool isActive)
{
    switch (action)
    {
    case MoveUp:
        directions[UP] = isActive;
        break;
    case MoveLeft:
        directions[LEFT] = isActive;
        break;
    case MoveDown:
        directions[DOWN] = isActive;
        break;
    case MoveRight:
        directions[RIGHT] = isActive;
        break;
    case Shoot:
        break;
    case Menu:
        return false;
    }
    return true;
}

/*
 * Same as above but using the key binding map
 */
bool Player::handleAction(sf::Keyboard::Key key, bool isActive)
{
    //If there isn't a binding for key, do nothing
    return handleAction(keyBinding[key], isActive);
}

void Player::update()
{
    sf::Vector2f velocity;

    if (directions[UP])
        velocity.y -= getSpeed();
    if (directions[LEFT])
        velocity.x -= getSpeed();
    if (directions[DOWN])
        velocity.y += getSpeed();
    if (directions[RIGHT])
        velocity.x += getSpeed();

    setVelocity(velocity);

    //Update crosshair
    crosshair->update(getPosition());
}

void Player::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}


