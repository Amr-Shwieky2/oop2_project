#include "Logic.h"
#include <iostream>

Logic::Logic() :m_player1(Singleton::instance().getPlayerCharacter1()),
    m_sidebar(800, 50), m_EndGame(false), m_isGamePaused(false), 
    m_savedPlayerVelocity1(0)
{
    if (!m_font.loadFromFile("arial.ttf")) {
        std::cerr << "Couldn't load the font!" << std::endl;
        std::exit(-1);
    }
    std::srand(static_cast<unsigned>(std::time(nullptr)));

}



bool Logic::mouseEvent(sf::RenderWindow& window)
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f worldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                sf::Vector2i transformedMousePos = static_cast<sf::Vector2i>(worldPos);
                if (m_sidebar.isPaused(transformedMousePos)) {
                    Singleton::instance().getSoundManager().playSound("click");
                    pauseGame();
                    return true;
                }
            }
        }
    }
    return false;
};

void Logic::pauseGame()
{
    m_isGamePaused = true;
    saveState();
}

void Logic::resumeGame()
{
    m_isGamePaused = false;
    restoreState();
}
