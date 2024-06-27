#pragma once
#include "BaseScreen.h"
#include "Singleton.h"
#include <SFML/Graphics.hpp>
#include <vector>

class HighScoreScreen : public BaseScreen {
public:
    HighScoreScreen();
    Screens_m handleEvents(sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window) override;

private:
    void updateHighScores();

    sf::Sprite m_screen;
    sf::IntRect m_backButton;
    sf::Font m_font;
    std::vector<sf::Text> m_highScoreTexts;
};
