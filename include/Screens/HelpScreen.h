#pragma once
#include "BaseScreen.h"
#include "Singleton.h"
#include <SFML/Graphics.hpp>
#include <vector>

// Class representing the help screen
class HelpScreen : public BaseScreen {
public:
    HelpScreen();
    Screens_m handleEvents(sf::RenderWindow& window) override; // Handle events for the help screen
    void render(sf::RenderWindow& window) override; // Render the help screen

private:
    sf::Sprite m_screen; // Background sprite for the help screen
    sf::RectangleShape m_backButton; // Back button to return to the menu

    sf::Font m_font; // Font for the text
    std::vector<sf::Text> m_Texts; // Texts for the help information
};
