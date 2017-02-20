#include "player.h"

Player::Player()
{
    //Initial hardcoded keybindings
    keyBinding[sf::Keyboard::W] = keyBinding[sf::Keyboard::Up] = MoveUp;
    keyBinding[sf::Keyboard::A] = keyBinding[sf::Keyboard::Left] = MoveLeft;
    keyBinding[sf::Keyboard::S] = keyBinding[sf::Keyboard::Down] = MoveDown;
    keyBinding[sf::Keyboard::D] = keyBinding[sf::Keyboard::Right] = MoveRight;
    keyBinding[sf::Keyboard::Escape] = Menu;

    if (!loadTexture("resources/monkey.png"))
    {
        //TODO: Handle error
        throw std::runtime_error("Couldn't load texture");
    }
    setPosition(200, 200);
    sprite.setOrigin(20, 20);
    setSpeed(250.0);
    setOrientation(RIGHT);
    stop();
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
    Action action = keyBinding[key];
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
    default:
        break;
    }
    return true;
}
