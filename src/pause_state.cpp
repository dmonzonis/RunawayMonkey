#include "pause_state.h"
#include "resource.h"
#include "resource_identifiers.h"
#include "utility.h"

PauseState::PauseState(StateManager &manager, Context context)
    : State(manager, context), options(), optionIndex(0) {
    sf::Font &font = context.fonts->get(Fonts::Main);
    sf::Vector2f viewSize = context.window->getView().getSize();

    sf::Text resumeOption;
    resumeOption.setFont(font);
    resumeOption.setString("Resume");
    centerOrigin(resumeOption);
    resumeOption.setPosition(viewSize / 2.f);
    options.push_back(resumeOption);

    sf::Text quitOption;
    quitOption.setFont(font);
    quitOption.setString("Quit");
    centerOrigin(quitOption);
    quitOption.setPosition(resumeOption.getPosition() +
                           sf::Vector2f(0.f, 30.f));
    options.push_back(quitOption);

    updateOptionText();
}

bool PauseState::update(sf::Time dt) { return false; }

void PauseState::draw() {
    sf::RenderWindow &window = *getContext().window;
    window.setView(window.getDefaultView());
    for (auto option : options)
        window.draw(option);
}

bool PauseState::handleEvent(const sf::Event &event) {
    if (event.type == sf::Event::KeyPressed &&
        event.key.code == sf::Keyboard::Return) {
        if (optionIndex == Resume) {
            popState();
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

void PauseState::updateOptionText() {
    if (options.empty())
        return;

    for (auto &text : options)
        text.setFillColor(sf::Color::White);

    options[optionIndex].setFillColor(sf::Color::Red);
}
