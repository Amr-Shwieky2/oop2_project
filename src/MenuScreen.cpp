#include "MenuScreen.h"

MenuScreen::MenuScreen() :
    m_playButton(410, 381, 655 - 410, 445 - 381),
    m_helpButton(412, 470, 657 - 412, 541 - 470),
    m_settingsButton(410, 559, 659 - 410, 630 - 559),
    m_topScoresButton(412, 650, 659 - 412, 718 - 650),
    m_exitButton(410, 741, 653 - 410, 807 - 741)
{
    m_screen.setTexture(*(Singleton::instance().getScreen(MENU_m)));
}

Screens_m MenuScreen::handleEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            window.close();
            return MENU_m;  // or a specific screen type for closing
        case sf::Event::MouseButtonReleased:
            if (event.mouseButton.button == sf::Mouse::Left) {
                Menu_c button = getMenuButton(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                switch (button) {
                case PLAY_GAME_c:
                    return PLAY_GAME_m;
                case HELP_c:
                    return HELP_m;
                case SETTINGS_c:
                    return SETTINGS_m;
                case HIGH_SCOORE_c:
                    return HIGH_SCOORE_m;
                case EXIT_c:
                    window.close();
                    return MENU_m;  // or a specific screen type for exit
                default:
                    break;
                }
            }
            break;
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
    else if (m_helpButton.contains(mousePos)) {
        return HELP_c;
    }
    else if (m_settingsButton.contains(mousePos)) {
        return SETTINGS_c;
    }
    else if (m_topScoresButton.contains(mousePos)) {
        return HIGH_SCOORE_c;
    }
    else if (m_exitButton.contains(mousePos)) {
        return EXIT_c;
    }
    return Menu_c();
}
