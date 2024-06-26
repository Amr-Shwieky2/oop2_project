#pragma once
#include "BaseScreen.h"
#include "Singleton.h"
#include <SFML/Graphics.hpp>
#include <vector>

class HighScoreScreen : public BaseScreen {
public:
    HighScoreScreen();
    void update();
    Screens_m handleEvents(sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window) override;

private:
    sf::Sprite m_screen;
    sf::IntRect m_backButton;
    sf::Font m_font;
    std::vector<sf::Text> m_highScoreTexts;  // Text objects for displaying high scores
};
