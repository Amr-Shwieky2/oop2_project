#pragma once
#include "BaseScreen.h"
#include "Singleton.h"

class HelpScreen : public BaseScreen {
public:
    HelpScreen();
    Screens_m handleEvents(sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window) override;

private:
    sf::Sprite m_screen;
    sf::IntRect m_backButton;
};
