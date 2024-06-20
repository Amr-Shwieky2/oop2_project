#include "PlayerSelectionScreen.h"

PlayerSelectionScreen::PlayerSelectionScreen() :
    onePlayerButton(435, 460, 645 - 435, 520 - 460),
    twoPlayersButton(435, 580, 645 - 435, 635 - 580),
    backButton(490, 150, 580 - 490, 220 - 150) {
    m_screen.setTexture(*(Singleton::instance().getScreen(PLAY_GAME_m)));
}

Screens_m PlayerSelectionScreen::handleEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            window.close();
            return PLAY_GAME_m;  // or a specific screen type for closing
        case sf::Event::MouseButtonReleased:
            if (event.mouseButton.button == sf::Mouse::Left) {
                Chooseen button = getChooseButton(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                switch (button) {
                case ONE_PLAYER:

                    Singleton::instance().getSoundManager().playSound("click"); // Play click sound
                    return C1_m;  // Return to character selection for one player
                case TWO_PLAYERS:
                    Singleton::instance().getSoundManager().playSound("click"); // Play click sound
                    return C2_m;  // Return to character selection for two players
                case BACK:
                    Singleton::instance().getSoundManager().playSound("click"); // Play click sound
                    return MENU_m;  // Return to menu screen
                default:
                    break;
                }
            }
            break;
        }
    }
    return PLAY_GAME_m;
}

void PlayerSelectionScreen::render(sf::RenderWindow& window) {
    window.draw(m_screen);
}

Chooseen PlayerSelectionScreen::getChooseButton(sf::Vector2i mousePos) {
    if (onePlayerButton.contains(mousePos)) {
        return ONE_PLAYER;
    }
    else if (twoPlayersButton.contains(mousePos)) {
        return TWO_PLAYERS;
    }
    else if (backButton.contains(mousePos)) {
        return BACK;
    }
    return Chooseen();
}
