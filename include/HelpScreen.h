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
    sf::RectangleShape m_backButton;


    sf::Font m_font;
    std::vector<sf::Text> m_Texts;
};
