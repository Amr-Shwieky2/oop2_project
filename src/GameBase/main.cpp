#include "Screens.h"
#include "GameLogic.h"
#include "Singleton.h"
#include <SFML/Graphics.hpp>

int main() {
    //logic mood
    /*sf::RenderWindow m_window;
    sf::Texture* texture = Singleton::instance().getScreen(GAME_m);
    sf::Vector2u imageSize = texture->getSize();
    m_window.create(sf::VideoMode(imageSize.x, imageSize.y + 50 ), "Game Window");
    GameLogic g;
    g.initialize(m_window);
    g.handleEvents(m_window);*/

    //game moode
    Screens s;
    s.run();
    return 0;
}
