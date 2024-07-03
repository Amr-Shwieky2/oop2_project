#pragma once

#include <SFML/Graphics.hpp>
#include "Singleton.h"
#include "BaseScreen.h"
#include <iostream>
#include <cmath>

class PauseScreen : public BaseScreen
{
public:
    PauseScreen();

    Screens_m handleEvents(sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window) override;



private:
    void updateWavingText(sf::Vector2i mousePos);

    sf::Sprite m_screen;

    sf::IntRect m_titleRect;
    sf::IntRect m_continue;
    sf::IntRect m_settings;
    std::vector<sf::Text> m_PauseScreenTexts;
    std::vector<sf::RectangleShape> m_Rectangles;
    sf::Font m_font;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Clock m_waveClock;

};