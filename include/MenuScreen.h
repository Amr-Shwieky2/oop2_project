#pragma once
#include "BaseScreen.h"
#include "Singleton.h"

class MenuScreen : public BaseScreen {
public:
    MenuScreen();
    Screens_m handleEvents(sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window) override;

private:
    sf::Sprite m_screen;
    Menu_c getMenuButton(sf::Vector2i mousePos);

    // Define the rectangles for menu options
    sf::IntRect m_titleRect;
    sf::IntRect m_playButton;
    sf::IntRect m_helpButton;
    sf::IntRect m_settingsButton;
    sf::IntRect m_topScoresButton;
    sf::IntRect m_exitButton;
    sf::Font m_font;
    std::vector<sf::Text> m_Texts;
    std::vector<sf::RectangleShape> m_Rectangles;

};
