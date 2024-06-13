#include "HelpScreen.h"

HelpScreen::HelpScreen() : m_backButton(400, 515, 570 - 400, 535 - 515)
{
    m_screen.setTexture(*(Singleton::instance().getScreen(HELP_m)));
}

Screens_m HelpScreen::handleEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            window.close();
            return HELP_m;  // or a specific screen type for closing
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
    return HELP_m;
}

void HelpScreen::render(sf::RenderWindow& window) {
    window.draw(m_screen);
}
