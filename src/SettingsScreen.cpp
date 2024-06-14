#include "SettingsScreen.h"
#include <iostream>

SettingsScreen::SettingsScreen() :
    m_backButton(540, 495, 755 - 540, 540 - 495),
    m_musicVolume(50), // Initial volume set to 50%
    m_effectsVolume(50) // Initial volume set to 50%
{
    m_screen.setTexture(*(Singleton::instance().getScreen(SETTINGS_m)));

    // Initialize the effects volume bar
    m_effectsBar.setSize(sf::Vector2f(200, 10)); // Increased height
    m_effectsBar.setFillColor(sf::Color::White);
    m_effectsBar.setPosition(525, 318); // Updated position

    // Initialize the effects volume dot
    m_effectsDot.setRadius(10);
    m_effectsDot.setFillColor(sf::Color::Red);
    m_effectsDot.setPosition(525 + m_effectsVolume * 2 - 10, 318 - 5); // Updated position based on volume

    // Initialize the music volume bar
    m_musicBar.setSize(sf::Vector2f(200, 10)); // Increased height
    m_musicBar.setFillColor(sf::Color::White);
    m_musicBar.setPosition(525, 426); // Updated position

    // Initialize the music volume dot
    m_musicDot.setRadius(10);
    m_musicDot.setFillColor(sf::Color::Red);
    m_musicDot.setPosition(525 + m_musicVolume * 2 - 10, 426 - 5); // Updated position based on volume

    // Set initial volumes
    Singleton::instance().getSoundManager().playMusic();
    Singleton::instance().getSoundManager().setMusicVolume(m_musicVolume);
    Singleton::instance().getSoundManager().setEffectsVolume(m_effectsVolume);
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
                    Singleton::instance().getSoundManager().playSound("click"); // Play click sound
                    return MENU_m;  // Return to menu screen
                }
                if (m_effectsBar.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    m_effectsVolume = (mousePos.x - 525) / 2.0f;
                    m_effectsDot.setPosition(525 + m_effectsVolume * 2 - 10, 318 - 5);
                    updateVolume();
                }
                if (m_musicBar.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    m_musicVolume = (mousePos.x - 525) / 2.0f;
                    m_musicDot.setPosition(525 + m_musicVolume * 2 - 10, 426 - 5);
                    updateVolume();
                }
            }
            break;
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
