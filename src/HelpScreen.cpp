#include "HelpScreen.h"

HelpScreen::HelpScreen() : m_backButton(400, 515, 170, 20) {
    m_screen.setTexture(*(Singleton::instance().getScreen(HELP_m)));
}

Screens_m HelpScreen::handleEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            return HELP_m;
        }
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
            if (m_backButton.contains(mousePos)) {
                Singleton::instance().getSoundManager().playSound("click");
                return MENU_m;
            }
        }
    }
    return HELP_m;
}

void HelpScreen::render(sf::RenderWindow& window) {
    window.draw(m_screen);
}
