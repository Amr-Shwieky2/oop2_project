#pragma once

#include <SFML/Graphics.hpp>
#include "Singleton.h"
#include "BaseScreen.h"
#include <iostream>
#include <cmath>

// Class representing the pause screen
class PauseScreen : public BaseScreen {
public:
    PauseScreen(); // Constructor

    Screens_m handleEvents(sf::RenderWindow& window) override; // Handle events for the pause screen
    void render(sf::RenderWindow& window) override; // Render the pause screen

private:
    void updateWavingText(sf::Vector2i mousePos); // Update the waving text effect

    sf::Sprite m_screen; // Background sprite for the pause screen

    sf::IntRect m_titleRect; // Rectangle for the title
    sf::IntRect m_continue; // Rectangle for the continue button
    sf::IntRect m_settings; // Rectangle for the settings button
    std::vector<sf::Text> m_PauseScreenTexts; // Texts for the pause screen options
    std::vector<sf::RectangleShape> m_Rectangles; // Rectangles for the pause screen options
    sf::Font m_font; // Font for the text
    sf::Texture backgroundTexture; // Background texture
    sf::Sprite backgroundSprite; // Background sprite
    sf::Clock m_waveClock; // Clock for the waving text effect
};
