#include "TwoPlayerLogic.h"
#include "Singleton.h"

TwoPlayerLogic::TwoPlayerLogic()
    : m_player2(Singleton::instance().getPlayerCharacter2()),
    m_sidebar(800, 50),
    m_savedPlayerVelocity2(0) {
    // Initialize other members as needed
}

Screens_m TwoPlayerLogic::handleEvents(sf::RenderWindow& window) {
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

void TwoPlayerLogic::render(sf::RenderWindow& window) {
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

void TwoPlayerLogic::initialize(sf::RenderWindow& window) {
    m_logic.initialize(window, m_player1, m_map);
    m_logic.initialize(window, m_player2, m_map);
}

void TwoPlayerLogic::update(float deltaTime, sf::RenderWindow& window) {
    m_player1.update(deltaTime, sf::Keyboard::A, sf::Keyboard::D); // Left player controls
    m_player2.update(deltaTime, sf::Keyboard::Left, sf::Keyboard::Right);

    m_map.collision(m_player1);
    m_map.update(deltaTime, window, m_player1);

    m_map.collision(m_player2);
    m_map.update(deltaTime, window, m_player2);

    CenterView(window);

    m_logic.isFail(m_player1, m_EndGame);
    m_logic.isFail(m_player2, m_EndGame);

    m_sidebar.update(m_player1.getScore(), m_player1.getLives(), m_player2.getScore(), m_player2.getLives());

    if (m_player1.hasFallen() || m_player2.hasFallen()) {
        m_EndGame = true;
    }
}

void TwoPlayerLogic::showEndBadge(sf::RenderWindow& window) {
    if (m_player1.hasFallen()) {
        m_logic.showEndBadge(window, "The winner is: " + Singleton::instance().getPlayerName2(), m_EndGame);
    }
    else if (m_player2.hasFallen()) {
        m_logic.showEndBadge(window, "The winner is: " + Singleton::instance().getPlayerName1(), m_EndGame);
    }
    else {
        m_logic.showEndBadge(window, "It's a tie!", m_EndGame);
    }
}

void TwoPlayerLogic::CenterView(sf::RenderWindow& window)
{
    if (m_player1.getPosition().y > m_player2.getPosition().y)
        m_logic.CenterView(window, m_player1);
    else
        m_logic.CenterView(window, m_player2);
}

void TwoPlayerLogic::saveState() {
    m_logic.saveState(m_savedPlayerPosition1, m_savedPlayerVelocity1,
        m_savedPlatformStates1, m_savedObjectStates1, m_player1, m_map);
    m_logic.saveState(m_savedPlayerPosition2, m_savedPlayerVelocity2,
        m_savedPlatformStates2, m_savedObjectStates2, m_player2, m_map);
}

void TwoPlayerLogic::restoreState() {
    m_logic.restoreState(m_savedPlayerPosition1, m_savedPlayerVelocity1,
        m_savedPlatformStates1, m_savedObjectStates1, m_player1, m_map);
    m_logic.restoreState(m_savedPlayerPosition2, m_savedPlayerVelocity2,
        m_savedPlatformStates2, m_savedObjectStates2, m_player2, m_map);
}

Screens_m TwoPlayerLogic::updateScore() {
    if (m_player1.hasFallen()) {
        LoadingManager::instance().updateHighScore(Singleton::instance().getPlayerName2(), m_player1.getScore());
    }
    else if (m_player2.hasFallen()) {
        LoadingManager::instance().updateHighScore(Singleton::instance().getPlayerName1(), m_player2.getScore());
    }
    return Screens_m::HIGH_SCOORE_m;
}

// Handle mouse events
bool TwoPlayerLogic::mouseEvent(sf::RenderWindow& window) {
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
}

