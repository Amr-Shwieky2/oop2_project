#pragma once
#include "BaseScreen.h"
#include "Singleton.h"

class PlayerSelectionScreen : public BaseScreen {
public:
    PlayerSelectionScreen();
    Screens_m handleEvents(sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window) override;

private:
    sf::Sprite m_screen;
    Chooseen getChooseButton(sf::Vector2i mousePos);

    // Define the rectangles for play mode options
    sf::IntRect onePlayerButton;
    sf::IntRect twoPlayersButton;
    sf::IntRect backButton;
};
