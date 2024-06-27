#include "SettingsScreen.h"

SettingsScreen::SettingsScreen()
    : m_backButton(540, 495, 215, 45),
    m_musicVolume(50),
    m_effectsVolume(50) {
    m_screen.setTexture(*(Singleton::instance().getScreen(SETTINGS_m)));

    m_effectsBar.setSize(sf::Vector2f(200, 10));
    m_effectsBar.setFillColor(sf::Color::White);
    m_effectsBar.setPosition(525, 318);

    m_effectsDot.setRadius(10);
    m_effectsDot.setFillColor(sf::Color::Red);
    m_effectsDot.setPosition(525 + m_effectsVolume * 2 - 10, 318 - 5);

    m_musicBar.setSize(sf::Vector2f(200, 10));
    m_musicBar.setFillColor(sf::Color::White);
    m_musicBar.setPosition(525, 426);

    m_musicDot.setRadius(10);
    m_musicDot.setFillColor(sf::Color::Red);
    m_musicDot.setPosition(525 + m_musicVolume * 2 - 10, 426 - 5);
}

Screens_m SettingsScreen::handleEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            return SETTINGS_m;
        }
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
            if (m_backButton.contains(mousePos)) {
                Singleton::instance().getSoundManager().playSound("click");
                return MENU_m;
            }
            if (m_effectsBar.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                m_effectsVolume = (mousePos.x - 525) / 2.0f;
                m_effectsDot.setPosition(525 + m_effectsVolume * 2 - 10, 318 - 5);
                updateVolume();
            }
            if (m_musicBar.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                m_musicVolume = (mousePos.x - 525) / 2.0f;
                m_musicDot.setPosition(525 + m_musicVolume * 2 - 10, 426 - 5);
                updateVolume();
            }
        }
    }
    return SETTINGS_m;
}

void SettingsScreen::render(sf::RenderWindow& window) {
    window.draw(m_screen);
    window.draw(m_effectsBar);
    window.draw(m_effectsDot);
    window.draw(m_musicBar);
    window.draw(m_musicDot);
}

void SettingsScreen::updateVolume() {
    Singleton::instance().getSoundManager().setMusicVolume(m_musicVolume);
    Singleton::instance().getSoundManager().setEffectsVolume(m_effectsVolume);
}
