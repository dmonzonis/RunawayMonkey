#include "player.h"

#include <iostream>

#include "command.h"
#include "projectile.h"
#include "utility.h"

Player::Player() {
    // Initial hardcoded keybindings
    // TODO: Make Settings class to handle this
    keyBinding[sf::Keyboard::W] = MoveUp;
    keyBinding[sf::Keyboard::A] = MoveLeft;
    keyBinding[sf::Keyboard::S] = MoveDown;
    keyBinding[sf::Keyboard::D] = MoveRight;
    // TODO: remove Debug keys for release
    keyBinding[sf::Keyboard::N] = Debug1;
    keyBinding[sf::Keyboard::M] = Debug2;
}

void Player::handleEvent(const sf::Event &event, CommandQueue &commands) {
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Right) {
        // Shoot a banana!
        if (playerActor->getAmmo() > 0) {
            playerActor->shoot(Projectile::Banana, &commands);
            playerActor->giveAmmo(-1);
        }
    }
}

void Player::handleRealTimeInput(CommandQueue &commands) {
    // Check if any bound keys are being pressed and act accordingly
    for (auto keyBind : keyBinding) {
        if (sf::Keyboard::isKeyPressed(keyBind.first) &&
            isRealTimeAction(keyBind.second)) {
            commands.push(actionBinding[keyBind.second]);
        }
    }
    // Check if left mouse button is being pressed
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        // Shoot some poop!
        playerActor->shoot(Projectile::Poop, &commands);
    }
}

void Player::assignKey(Action action, sf::Keyboard::Key key) {
    // Check if action is already mapped and remove older mapping if it is
    for (auto it = keyBinding.begin(); it != keyBinding.end(); ++it) {
        if (it->second == action) {
            it = keyBinding.erase(it);
        }
    }
    keyBinding[key] = action;
}

sf::Keyboard::Key Player::getAssignedKey(Action action) const {
    for (auto it = keyBinding.begin(); it != keyBinding.end(); ++it) {
        if (it->second == action)
            return it->first;
    }
    return sf::Keyboard::Unknown;
}

Category::Type Player::getCategory() const { return Category::Player; }

void Player::setActor(Actor *actor) {
    playerActor = actor;
    float speed = playerActor->getSpeed();
    actionBinding[MoveUp] = Command(MoveActor(0.f, -speed), Category::Player);
    actionBinding[MoveLeft] = Command(MoveActor(-speed, 0.f), Category::Player);
    actionBinding[MoveDown] = Command(MoveActor(0.f, speed), Category::Player);
    actionBinding[MoveRight] = Command(MoveActor(speed, 0.f), Category::Player);
}

Actor *Player::getActor() const { return playerActor; }

bool Player::isRealTimeAction(Action action) {
    switch (action) {
    case MoveUp:
    case MoveLeft:
    case MoveDown:
    case MoveRight:
        return true;
    default:
        return false;
    }
}
