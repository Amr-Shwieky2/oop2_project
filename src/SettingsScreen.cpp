#include "SettingsScreen.h"

SettingsScreen::SettingsScreen() :
    m_backButton(540, 495, 755 - 540, 540 - 495) {
    m_screen.setTexture(*(Singleton::instance().getScreen(SETTINGS_m)));
}

Screens_m SettingsScreen::handleEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            window.close();
            return SETTINGS_m;  // or a specific screen type for closing
        case sf::Event::MouseButtonReleased:
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
                if (m_backButton.contains(mousePos)) {
                    return MENU_m;  // Return to menu screen
                }
            }
            break;
        }
    }
    return SETTINGS_m;
}

void SettingsScreen::render(sf::RenderWindow& window) {
    window.draw(m_screen);
}
