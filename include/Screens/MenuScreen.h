#pragma once
#include "BaseScreen.h"
#include "Singleton.h"
#include <SFML/Graphics.hpp>
#include <vector>

// Class representing the menu screen
class MenuScreen : public BaseScreen {
public:
    MenuScreen();
    Screens_m handleEvents(sf::RenderWindow& window) override; // Handle events for the menu screen
    void render(sf::RenderWindow& window) override; // Render the menu screen

private:
    sf::Sprite m_screen; // Background sprite for the menu
    Menu_c getMenuButton(sf::Vector2i mousePos); // Get the button based on mouse position
    void updateWavingText(sf::Vector2i mousePos); // Update text animation

    // Define the rectangles for menu options
    sf::IntRect m_titleRect;
    sf::IntRect m_playButton;
    sf::IntRect m_helpButton;
    sf::IntRect m_settingsButton;
    sf::IntRect m_topScoresButton;
    sf::IntRect m_exitButton;

    sf::Font m_font; // Font for the menu text
    std::vector<sf::Text> m_Texts; // Texts for the menu options
    std::vector<sf::RectangleShape> m_Rectangles; // Rectangles for the menu options
    sf::Clock m_waveClock; // Clock for text animation
    bool m_isWaving; // Flag for text animation
};
