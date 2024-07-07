#include "GameLogic.h"
#include <iostream>

GameLogic::GameLogic()
{
    
}

void GameLogic::initialize(sf::RenderWindow& window) 
{ 
    m_logic.initialize(window, m_player1, m_map);
}

Screens_m GameLogic::handleEvents(sf::RenderWindow& window) 
{
    m_player1.setTexture(Singleton::instance().getPlayerCharacter1());
    while (window.isOpen()) {
        if (mouseEvent(window))
            return PAUSE_m;

        float deltaTime = m_clock.restart().asSeconds();
        if (!m_isGamePaused) {
            update(deltaTime, window);
        }
        render(window);
        if (m_EndGame) {
            showEndBadge(window);
            //resetGame();
            return updateScore();
        }
    }
    return Screens_m::GAME_m;
}

void GameLogic::update(float deltaTime, sf::RenderWindow& window) 
{ 
    m_player1.update(deltaTime, sf::Keyboard::Left, sf::Keyboard::Right);
    m_logic.update(deltaTime, window, m_player1, m_map, m_sidebar, m_EndGame);
}



void GameLogic::showEndBadge(sf::RenderWindow& window)
{
    m_logic.showEndBadge(window, "Score: " + std::to_string(m_map.getScore()), m_EndGame);
}


void GameLogic::render(sf::RenderWindow& window)
{ 
    m_logic.render(window, m_player1, m_map, m_sidebar, m_screen);
}

void GameLogic::saveState()
{ 
    m_logic.saveState(m_savedPlayerPosition1, m_savedPlayerVelocity1,
        m_savedPlatformStates1, m_savedObjectStates1, m_player1, m_map);
}

void GameLogic::restoreState() 
{
    m_logic.restoreState(m_savedPlayerPosition1, m_savedPlayerVelocity1,
        m_savedPlatformStates1, m_savedObjectStates1, m_player1, m_map);
}

Screens_m GameLogic::updateScore()
{
    LoadingManager::instance().updateHighScore(Singleton::instance().getPlayerName1(), m_map.getScore());
    return Screens_m::HIGH_SCOORE_m;
}

