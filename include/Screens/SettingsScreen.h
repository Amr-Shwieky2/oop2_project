#pragma once

#include <SFML/Graphics.hpp>
#include "BaseScreen.h"
#include "Singleton.h"

// Class representing the settings screen
class SettingsScreen : public BaseScreen {
public:
    SettingsScreen(); // Constructor
    Screens_m handleEvents(sf::RenderWindow& window) override; // Handle events for the settings screen
    void render(sf::RenderWindow& window) override; // Render the settings screen

private:
    sf::Sprite m_screen; // Background sprite for the settings screen
    sf::IntRect m_backButton; // Rectangle for the back button
    sf::RectangleShape m_musicBar; // Music volume bar
    sf::RectangleShape m_effectsBar; // Effects volume bar
    sf::RectangleShape m_BackGround; // Background rectangle
    sf::RectangleShape m_backButtonShape; // Shape for the back button
    sf::CircleShape m_musicDot; // Dot for music volume
    sf::CircleShape m_effectsDot; // Dot for effects volume
    float m_musicVolume; // Music volume level
    float m_effectsVolume; // Effects volume level
    sf::Font m_font; // Font for the text
    std::vector<sf::Text> m_Texts; // Texts for the settings options
    void updateVolume(); // Update the volume settings
};
