#include "HighScoreScreen.h"

HighScoreScreen::HighScoreScreen() :
    m_backButton(230, 800, 465 - 230, 835 - 800) {
    m_screen.setTexture(*(Singleton::instance().getScreen(HIGH_SCOORE_m)));
}

Screens_m HighScoreScreen::handleEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            window.close();
            return HIGH_SCOORE_m;  // or a specific screen type for closing
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
    return HIGH_SCOORE_m;
}

void HighScoreScreen::render(sf::RenderWindow& window) {
    window.draw(m_screen);
}
