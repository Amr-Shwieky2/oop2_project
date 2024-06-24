#include "Screens.h"
#include "GameLogic.h"
#include "Singleton.h"
#include <SFML/Graphics.hpp>

int main() {

    sf::RenderWindow m_window;
    sf::Texture* texture = Singleton::instance().getScreen(GAME_m);
    sf::Vector2u imageSize = texture->getSize();
    m_window.create(sf::VideoMode(imageSize.x, imageSize.y), "Game Window");
    GameLogic g;
    g.handleEvents(m_window);
    return 0;
}
