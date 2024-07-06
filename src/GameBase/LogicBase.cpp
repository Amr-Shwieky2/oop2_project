#include "LogicBase.h"

LogicBase::LogicBase() :m_player1(Singleton::instance().getPlayerCharacter1()),
    m_sidebar(800, 50), m_EndGame(false), m_isGamePaused(false), 
    m_savedPlayerVelocity1(0)
{
    
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    m_screen.setTexture(*(LoadingManager::instance().getScreen(GAME_m)));

}

bool LogicBase::mouseEvent(sf::RenderWindow& window)
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

void LogicBase::pauseGame()
{
    m_isGamePaused = true;
    saveState();
}

void LogicBase::resumeGame()
{
    m_isGamePaused = false;
    restoreState();
}
