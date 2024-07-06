#include "TwoPlayerLogic.h"

TwoPlayerLogic::TwoPlayerLogic()
    :
    m_player2(Singleton::instance().getPlayerCharacter2()),
    m_sidebar2(800, 50),
    m_savedPlayerVelocity2(0)
{
   
}

Screens_m TwoPlayerLogic::handleEvents(sf::RenderWindow& window)
{
    //initializeViewsAndLine(window);
    m_player1.setTexture(Singleton::instance().getPlayerCharacter1());
    m_player2.setTexture(Singleton::instance().getPlayerCharacter2());

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
            return updateScore();
        }
    }
    return GAME_m;
}

void TwoPlayerLogic::render(sf::RenderWindow& window)
{
    window.clear();

    sf::View view = window.getView();
    float viewTop = view.getCenter().y - view.getSize().y / 2;

    for (int i = 0; i < 3; ++i) {
        m_screen.setPosition(0, viewTop + i * m_screen.getTexture()->getSize().y);
        window.draw(m_screen);
    }
    m_player1.draw(window);
    m_player2.draw(window);

    m_map.render(window);

    window.setView(window.getDefaultView());
    m_sidebar.draw(window);

    window.display();
}

void TwoPlayerLogic::initialize(sf::RenderWindow& window)
{
    m_logic.initialize(window, m_player1, m_map);
    m_logic.initialize(window, m_player2, m_map);
}


void TwoPlayerLogic::update(float deltaTime, sf::RenderWindow& window)
{
    m_player1.update(deltaTime, sf::Keyboard::A, sf::Keyboard::D); // Left player controls
    m_player2.update(deltaTime, sf::Keyboard::Left, sf::Keyboard::Right);

    m_logic.update(deltaTime, window, m_player1, m_map, m_sidebar, m_EndGame);
    m_logic.update(deltaTime, window, m_player2, m_map, m_sidebar, m_EndGame);
}

void TwoPlayerLogic::showEndBadge(sf::RenderWindow& window)
{
    if(m_map.getScore() > m_map2.getScore())
        m_logic.showEndBadge(window, "The win is: " + Singleton::instance().getPlayerName1(), m_EndGame);
    else
        m_logic.showEndBadge(window, "The win is: " + Singleton::instance().getPlayerName2(), m_EndGame);
}

void TwoPlayerLogic::saveState()
{
    m_logic.saveState(m_savedPlayerPosition1, m_savedPlayerVelocity1,
        m_savedPlatformStates1, m_savedObjectStates1, m_player1, m_map);
    m_logic.saveState(m_savedPlayerPosition2, m_savedPlayerVelocity2,
        m_savedPlatformStates2, m_savedObjectStates2, m_player2, m_map);
}

void TwoPlayerLogic::restoreState()
{
    m_logic.restoreState(m_savedPlayerPosition1, m_savedPlayerVelocity1,
        m_savedPlatformStates1, m_savedObjectStates1, m_player1, m_map);
    m_logic.restoreState(m_savedPlayerPosition2, m_savedPlayerVelocity2,
        m_savedPlatformStates2, m_savedObjectStates2, m_player2, m_map);
}

Screens_m TwoPlayerLogic::updateScore()
{
    LoadingManager::instance().updateHighScore(Singleton::instance().getPlayerName1(), m_map.getScore());
    LoadingManager::instance().updateHighScore(Singleton::instance().getPlayerName2(), m_map.getScore());
    return Screens_m::HIGH_SCOORE_m;
}
