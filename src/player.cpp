#include "player.h"

Player::Player(const TextureHolder& textures)
    : sprite(textures.get(Textures::Monkey))
    , crosshair(nullptr)
    , shooting(false)
{
    //Initial hardcoded keybindings
    //TODO: Make Settings class to handle this
    keyBinding[sf::Keyboard::W] = keyBinding[sf::Keyboard::Up] = MoveUp;
    keyBinding[sf::Keyboard::A] = keyBinding[sf::Keyboard::Left] = MoveLeft;
    keyBinding[sf::Keyboard::S] = keyBinding[sf::Keyboard::Down] = MoveDown;
    keyBinding[sf::Keyboard::D] = keyBinding[sf::Keyboard::Right] = MoveRight;
    keyBinding[sf::Keyboard::Escape] = Menu;
    //FIXME: remove Debug keys for release
    keyBinding[sf::Keyboard::N] = Debug1;
    keyBinding[sf::Keyboard::M] = Debug2;

    //Make hitbox from sprite bounds and set the origin to the center
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

bool Player::isShooting()
{
    return shooting;
}

void Player::setShooting(bool shoot)
{
    shooting = shoot;
}


/*
 * Handle given action. Returns false if game should quit, true otherwise
 */
int Player::handleAction(Action action, bool isActive)
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
        return 0;
    case Debug1:
        return 2;
    case Debug2:
        return 3;
    }
    return 1;
}

int Player::handleAction(sf::Keyboard::Key key, bool isActive)
{
    //If there isn't a binding for key, does nothing
    return handleAction(keyBinding[key], isActive);
}

void Player::update()
{
    //Compute velocity from moving directions and speed
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

    //Flip character if necessary
    flip(crosshair->getPosition());
}

void Player::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}


