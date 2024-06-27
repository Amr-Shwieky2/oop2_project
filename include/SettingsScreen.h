#pragma once
#include "BaseScreen.h"
#include "Singleton.h"
#include <SFML/Graphics.hpp>

class SettingsScreen : public BaseScreen {
public:
    SettingsScreen();
    Screens_m handleEvents(sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window) override;

private:
    void updateVolume();

    sf::Sprite m_screen;
    sf::IntRect m_backButton;
    sf::RectangleShape m_musicBar;
    sf::RectangleShape m_effectsBar;
    sf::CircleShape m_musicDot;
    sf::CircleShape m_effectsDot;
    float m_musicVolume;
    float m_effectsVolume;
};
