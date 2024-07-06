#include "Screens.h"
#include "GameLogic.h"
#include "Singleton.h"
#include <SFML/Graphics.hpp>

//int main() {
//    sf::RenderWindow window(sf::VideoMode(800, 600), "Witch Image");
//    sf::Texture texture;
//
//    if (!texture.loadFromFile("sharp.png")) {
//        return -1; // Error loading image
//    }
//
//    sf::Sprite sprite;
//    sprite.setTexture(texture);
//
//    while (window.isOpen()) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//
//        window.clear();
//        window.draw(sprite);
//        window.display();
//    }
//
//    return 0;
//}


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
