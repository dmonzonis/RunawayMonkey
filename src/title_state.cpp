#include "resource.h"
#include "resource_identifiers.h"
#include "title_state.h"
#include "utility.h"

TitleState::TitleState(StateManager &manager, Context context)
    : State(manager, context), text(), showText(true),
      textEffectTime(sf::Time::Zero) {
    backgroundSprite.setTexture(
        context.textures->get(Textures::TitleBackground));
    text.setFont(context.fonts->get(Fonts::Main));
    text.setString("Press a key to start");
    centerOrigin(text);
    text.setPosition(context.window->getView().getSize() / 2.f);
}

bool TitleState::update(sf::Time dt) {
    textEffectTime += dt;
    if (textEffectTime >= sf::seconds(0.5f)) {
        showText = !showText;
        textEffectTime = sf::Time::Zero;
    }
    return true;
}

void TitleState::draw() {
    sf::RenderWindow &window = *getContext().window;
    window.draw(backgroundSprite);
    if (showText)
        window.draw(text);
}

bool TitleState::handleEvent(const sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        popState();
        pushState(States::Game);
    }
    return true;
}
