#include "MenuScreen.h"
#include <iostream>

MenuScreen::MenuScreen()
    : m_playButton(410, 381, 245, 64),
    m_helpButton(412, 470, 245, 71),
    m_settingsButton(410, 559, 249, 71),
    m_topScoresButton(412, 650, 247, 68),
    m_exitButton(410, 741, 243, 66) {
    m_screen.setTexture(*(Singleton::instance().getScreen(MENU_m)));
}

Screens_m MenuScreen::handleEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            return MENU_m;
        }
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
            Menu_c button = getMenuButton(mousePos);
            switch (button) {
            case PLAY_GAME_c:
                Singleton::instance().getSoundManager().playSound("click");
                return PLAY_GAME_m;
            case HELP_c:
                Singleton::instance().getSoundManager().playSound("click");
                return HELP_m;
            case SETTINGS_c:
                Singleton::instance().getSoundManager().playSound("click");
                return SETTINGS_m;
            case HIGH_SCOORE_c:
                Singleton::instance().getSoundManager().playSound("click");
                return HIGH_SCOORE_m;
            case EXIT_c:
                Singleton::instance().getSoundManager().playSound("click");
                window.close();
                return MENU_m;
            default:
                break;
            }
        }
    }
    return MENU_m;
}

void MenuScreen::render(sf::RenderWindow& window) {
    window.draw(m_screen);
}

Menu_c MenuScreen::getMenuButton(sf::Vector2i mousePos) {
    if (m_playButton.contains(mousePos)) {
        return PLAY_GAME_c;
    }
    if (m_helpButton.contains(mousePos)) {
        return HELP_c;
    }
    if (m_settingsButton.contains(mousePos)) {
        return SETTINGS_c;
    }
    if (m_topScoresButton.contains(mousePos)) {
        return HIGH_SCOORE_c;
    }
    if (m_exitButton.contains(mousePos)) {
        return EXIT_c;
    }
    return Menu_c();
}
