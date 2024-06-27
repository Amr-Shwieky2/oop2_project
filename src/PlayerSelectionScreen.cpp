#include "PlayerSelectionScreen.h"

PlayerSelectionScreen::PlayerSelectionScreen()
    : m_onePlayerButton(435, 460, 210, 60),
    m_twoPlayersButton(435, 580, 210, 55),
    m_backButton(490, 150, 90, 70) {
    m_screen.setTexture(*(Singleton::instance().getScreen(PLAY_GAME_m)));
}

Screens_m PlayerSelectionScreen::handleEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            return PLAY_GAME_m;
        }
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            Chooseen button = getChooseButton(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
            switch (button) {
            case ONE_PLAYER:
                Singleton::instance().getSoundManager().playSound("click");
                return C1_m;
            case TWO_PLAYERS:
                Singleton::instance().getSoundManager().playSound("click");
                return C2_m;
            case BACK:
                Singleton::instance().getSoundManager().playSound("click");
                return MENU_m;
            default:
                break;
            }
        }
    }
    return PLAY_GAME_m;
}

void PlayerSelectionScreen::render(sf::RenderWindow& window) {
    window.draw(m_screen);
}

Chooseen PlayerSelectionScreen::getChooseButton(sf::Vector2i mousePos) {
    if (m_onePlayerButton.contains(mousePos)) {
        return ONE_PLAYER;
    }
    if (m_twoPlayersButton.contains(mousePos)) {
        return TWO_PLAYERS;
    }
    if (m_backButton.contains(mousePos)) {
        return BACK;
    }
    return Chooseen();
}
