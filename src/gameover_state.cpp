#include "gameover_state.h"
#include "resource.h"
#include "resource_identifiers.h"
#include "utility.h"

GameOverState::GameOverState(StateManager &manager, Context context)
    : State(manager, context), options(), optionIndex(0) {
    sf::Font &font = context.fonts->get(Fonts::Main);
    sf::Vector2f viewSize = context.window->getView().getSize();

    sf::Text resumeOption;
    resumeOption.setFont(font);
    resumeOption.setString("Retry");
    centerOrigin(resumeOption);
    resumeOption.setPosition(viewSize / 2.f);
    options.push_back(resumeOption);

    sf::Text quitOption;
    quitOption.setFont(font);
    quitOption.setString("Go to the main menu");
    centerOrigin(quitOption);
    quitOption.setPosition(resumeOption.getPosition() +
                           sf::Vector2f(0.f, 60.f));
    options.push_back(quitOption);

    updateOptionText();
}

bool GameOverState::update(sf::Time dt) {
    // TODO: change to true when the enemy behaviour is fixed
    return false;
}

void GameOverState::draw() {
    sf::RenderWindow &window = *getContext().window;
    window.setView(window.getDefaultView());
    for (auto option : options)
        window.draw(option);
}

bool GameOverState::handleEvent(const sf::Event &event) {
    if (event.type == sf::Event::KeyPressed &&
        event.key.code == sf::Keyboard::Return) {
        if (optionIndex == Retry) {
            popState();
            popState();
            pushState(States::Game);
        } else if (optionIndex == Quit) {
            clearStates();
            pushState(States::Title);
        }
    } else if (event.type == sf::Event::KeyPressed &&
               event.key.code == sf::Keyboard::Up) {
        if (optionIndex > 0)
            --optionIndex;
        else
            optionIndex = options.size() - 1;

        updateOptionText();
    } else if (event.type == sf::Event::KeyPressed &&
               event.key.code == sf::Keyboard::Down) {
        if (optionIndex < options.size() - 1)
            ++optionIndex;
        else
            optionIndex = 0;

        updateOptionText();
    }

    return false;
}

void GameOverState::updateOptionText() {
    if (options.empty())
        return;

    for (auto &text : options)
        text.setFillColor(sf::Color::White);

    options[optionIndex].setFillColor(sf::Color::Red);
}
