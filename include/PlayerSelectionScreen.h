#pragma once
#include "BaseScreen.h"
#include "Singleton.h"
#include <SFML/Graphics.hpp>

class PlayerSelectionScreen : public BaseScreen {
public:
    PlayerSelectionScreen();
    Screens_m handleEvents(sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window) override;

private:
    Chooseen getChooseButton(sf::Vector2i mousePos);

    sf::Sprite m_screen;
    sf::IntRect m_onePlayerButton;
    sf::IntRect m_twoPlayersButton;
    sf::IntRect m_backButton;
};
