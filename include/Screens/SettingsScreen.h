#pragma once

#include <SFML/Graphics.hpp>
#include "BaseScreen.h"
#include "Singleton.h"

class SettingsScreen : public BaseScreen {
public:
    SettingsScreen();  // Add previous screen parameter
    Screens_m handleEvents(sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window) override;

private:
    sf::Sprite m_screen;
    sf::IntRect m_backButton;
    sf::RectangleShape m_musicBar;
    sf::RectangleShape m_effectsBar;
    sf::RectangleShape m_BackGround;
    sf::RectangleShape m_backButtonShape;
    sf::CircleShape m_musicDot;
    sf::CircleShape m_effectsDot;
    float m_musicVolume;
    float m_effectsVolume;
    sf::Font m_font;
    std::vector<sf::Text> m_Texts;
    void updateVolume();
};