#pragma once
#include "BaseScreen.h"
#include "Singleton.h"
#include <SFML/Graphics.hpp>
#include <vector>

// Class representing the high score screen
class HighScoreScreen : public BaseScreen {
public:
    HighScoreScreen(); // Constructor
    void update(); // Update the high score texts
    Screens_m handleEvents(sf::RenderWindow& window) override; // Handle events for the high score screen
    void render(sf::RenderWindow& window) override; // Render the high score screen

private:
    sf::Sprite m_screen; // Background sprite for the high score screen
    sf::IntRect m_backButton; // Rectangle for the back button
    sf::RectangleShape m_backButtonShape; // Shape for the back button
    sf::Font m_font; // Font for the text
    sf::Text m_backText; // Text for the back button
    std::vector<sf::Text> m_highScoreTexts; // Text objects for displaying high scores
};
