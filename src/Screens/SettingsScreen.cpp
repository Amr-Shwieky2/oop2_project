#include "SettingsScreen.h"
#include "LoadingManager.h"
#include "GameException.h"
#include <iostream>

// Constructor to initialize the settings screen
SettingsScreen::SettingsScreen() :
    m_backButton(540, 495, 215, 45), // Initialize back button rectangle
    m_musicVolume(50), // Initial music volume set to 50%
    m_effectsVolume(50) // Initial effects volume set to 50%
{
    try {
        if (!m_font.loadFromFile("arial.ttf")) {
            throw GameException("Failed to load font");
        }
        m_screen.setTexture(*(LoadingManager::instance().getScreen(SETTINGS_m)));

        // Initialize the effects volume bar
        m_effectsBar.setSize(sf::Vector2f(200, 10)); // Set size of the effects bar
        m_effectsBar.setFillColor(sf::Color::White); // Set color of the effects bar
        m_effectsBar.setPosition(350, 318); // Set position of the effects bar

        // Initialize the effects volume dot
        m_effectsDot.setRadius(10); // Set radius of the effects dot
        m_effectsDot.setFillColor(sf::Color::Red); // Set color of the effects dot
        m_effectsDot.setPosition(350 + m_effectsVolume * 2 - 10, 318 - 5); // Set position of the effects dot based on volume

        // Initialize the music volume bar
        m_musicBar.setSize(sf::Vector2f(200, 10)); // Set size of the music bar
        m_musicBar.setFillColor(sf::Color::White); // Set color of the music bar
        m_musicBar.setPosition(350, 426); // Set position of the music bar

        // Initialize the music volume dot
        m_musicDot.setRadius(10); // Set radius of the music dot
        m_musicDot.setFillColor(sf::Color::Red); // Set color of the music dot
        m_musicDot.setPosition(350 + m_musicVolume * 2 - 10, 426 - 5); // Set position of the music dot based on volume

        // Initialize the background rectangle
        m_BackGround.setSize(sf::Vector2f(500, 400)); // Set size of the background
        m_BackGround.setOutlineThickness(5); // Set outline thickness of the background
        m_BackGround.setOutlineColor(sf::Color::Red); // Set outline color of the background
        m_BackGround.setFillColor(sf::Color::Black); // Set fill color of the background
        m_BackGround.setPosition(150, 150); // Set position of the background

        // Initialize the back button shape
        m_backButtonShape.setSize(sf::Vector2f(100, 50)); // Set size of the back button
        m_backButtonShape.setPosition(540, 495); // Set position of the back button
        m_backButtonShape.setFillColor(sf::Color::Red); // Set fill color of the back button
        m_backButtonShape.setOutlineColor(sf::Color::White); // Set outline color of the back button
        m_backButtonShape.setOutlineThickness(2); // Set outline thickness of the back button

        std::vector<sf::Vector2f> positions = {
            sf::Vector2f(290, 200), sf::Vector2f(160, 300),
            sf::Vector2f(185, 410), sf::Vector2f(560, 505)
        }; // Positions for texts

        std::string menuItems[] = {
            "--SOUND SETTINGS--", "SOUND EFFECTS", "MUSIC", "BACK"
        }; // Texts for the menu items

        for (int i = 0; i < 4; ++i) {
            sf::Text text(menuItems[i], m_font, 25); // Create text
            text.setPosition(positions[i]); // Set position of the text
            text.setFillColor(sf::Color::White); // Set color of the text
            m_Texts.push_back(text); // Add text to the vector
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Error initializing SettingsScreen: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error initializing SettingsScreen" << std::endl;
        throw;
    }
}

// Handle events for the settings screen
Screens_m SettingsScreen::handleEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        try {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                return SETTINGS_m;
            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);

                    if (m_effectsBar.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        m_effectsVolume = static_cast<float>((mousePos.x - m_effectsBar.getPosition().x) / (m_effectsBar.getSize().x * 0.01));
                        m_effectsDot.setPosition(m_effectsBar.getPosition().x + m_effectsVolume * 2 - 10, m_effectsBar.getPosition().y - 5);
                        updateVolume();
                    }
                    if (m_musicBar.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        m_musicVolume = static_cast<float>((mousePos.x - m_musicBar.getPosition().x) / (m_musicBar.getSize().x * 0.01));
                        m_musicDot.setPosition(m_musicBar.getPosition().x + m_musicVolume * 2 - 10, m_musicBar.getPosition().y - 5);
                        updateVolume();
                    }
                    if (m_backButtonShape.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        Singleton::instance().getSoundManager().playSound("click");
                        return MENU_m; // Return to the menu screen
                    }
                }
                break;
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Error handling events: " << e.what() << std::endl;
            throw;
        }
        catch (...) {
            std::cerr << "Unknown error handling events" << std::endl;
            throw;
        }
    }
    return SETTINGS_m;
}

// Render the settings screen
void SettingsScreen::render(sf::RenderWindow& window) {
    try {
        window.draw(m_screen);
        window.draw(m_BackGround);
        window.draw(m_effectsBar);
        window.draw(m_effectsDot);
        window.draw(m_musicBar);
        window.draw(m_musicDot);
        window.draw(m_backButtonShape);

        for (size_t i = 0; i < m_Texts.size(); ++i) {
            window.draw(m_Texts[i]);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error rendering SettingsScreen: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error rendering SettingsScreen" << std::endl;
        throw;
    }
}

// Update the volume settings
void SettingsScreen::updateVolume() {
    try {
        Singleton::instance().getSoundManager().setMusicVolume(m_musicVolume);
        Singleton::instance().getSoundManager().setEffectsVolume(m_effectsVolume);
    }
    catch (const std::exception& e) {
        std::cerr << "Error updating volume: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error updating volume" << std::endl;
        throw;
    }
}
