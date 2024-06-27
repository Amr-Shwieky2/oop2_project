#pragma once
#include "BaseScreen.h"
#include "Singleton.h"
#include <SFML/Graphics.hpp>

class MenuScreen : public BaseScreen {
public:
    MenuScreen();
    Screens_m handleEvents(sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window) override;

private:
    Menu_c getMenuButton(sf::Vector2i mousePos);

    sf::Sprite m_screen;
    sf::IntRect m_playButton;
    sf::IntRect m_helpButton;
    sf::IntRect m_settingsButton;
    sf::IntRect m_topScoresButton;
    sf::IntRect m_exitButton;
};
