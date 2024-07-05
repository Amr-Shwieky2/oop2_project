#include "GameLogic.h"
#include <iostream>

GameLogic::GameLogic()
    : m_isGamePaused(false), m_savedPlayerVelocity(0),
    m_EndGame(false), m_sidebar(800, 50), m_nextScreen(GAME_m),
    m_savedClockTime(0),
    m_player1(Singleton::instance().getPlayerCharacter1()) {
    if (!m_font.loadFromFile("arial.ttf")) {
        std::cerr << "Couldn't load the font!" << std::endl;
        std::exit(-1);
    }
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    m_screen.setTexture(*(LoadingManager::instance().getScreen(GAME_m)));
}

void GameLogic::initialize(sf::RenderWindow& window) {
    window.setFramerateLimit(60);
    m_map.initialize(window);
    m_player1.resetPosition(m_map.getPlayerStartX(), m_map.getPlayerStartY());
}

Screens_m GameLogic::handleEvents(sf::RenderWindow& window) {
    m_player1.setTexture(Singleton::instance().getPlayerCharacter1());
    sf::Event event;
    while (window.isOpen()) {
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
                        return PAUSE_m;
                    }
                }
            }
        }

        float deltaTime = m_clock.restart().asSeconds();
        if (!m_isGamePaused) {
            update(deltaTime, window);
        }
        render(window);
        if (m_EndGame) {
            LoadingManager::instance().updateHighScore(Singleton::instance().getPlayerName1(), m_map.getScore());
            return Screens_m::HIGH_SCOORE_m;
        }
    }
    return Screens_m::GAME_m;
}

void GameLogic::update(float deltaTime, sf::RenderWindow& window) {
    m_player1.update(deltaTime);
    m_map.collision(m_player1, deltaTime);
    m_map.update(deltaTime, window, m_player1);

    CenterView(window);
    isFail();
    m_sidebar.update(m_map.getScore(), static_cast<int>(m_map.getHeight()), m_player1.getLives());
}

void GameLogic::isFail() {
    if (m_player1.hasFallen() || m_player1.getLives() <= 0) {
        m_EndGame = true;
    }
}

void GameLogic::CenterView(sf::RenderWindow& window) {
    sf::View view = window.getView();
    view.setCenter(view.getCenter().x, m_player1.getPosition().y);
    window.setView(view);
}

void GameLogic::render(sf::RenderWindow& window) {
    window.clear();

    sf::View view = window.getView();
    float viewTop = view.getCenter().y - view.getSize().y / 2;

    for (int i = 0; i < 3; ++i) {
        m_screen.setPosition(0, viewTop + i * m_screen.getTexture()->getSize().y);
        window.draw(m_screen);
    }

    m_player1.draw(window);
    m_map.render(window);

    window.setView(window.getDefaultView());
    m_sidebar.draw(window);

    if (m_EndGame) {
        sf::RectangleShape scoreBackground(sf::Vector2f(300.0f, 100.0f));
        scoreBackground.setFillColor(sf::Color::Black);
        scoreBackground.setPosition(window.getView().getCenter().x - 150, window.getView().getCenter().y - 50);

        sf::Text scoreText;
        scoreText.setFont(m_font);
        scoreText.setString("Score: " + std::to_string(m_map.getScore()));
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(window.getView().getCenter().x - 140, window.getView().getCenter().y - 40);

        window.draw(scoreBackground);
        window.draw(scoreText);
        window.display();

        sf::sleep(sf::seconds(3.0));
    }
    window.display();
}

void GameLogic::saveState() {
    m_savedPlayerPosition = m_player1.getPosition();
    m_savedPlayerVelocity = m_player1.getVelocity();
    m_savedClockTime = m_clock.getElapsedTime().asSeconds();
    m_savedPlatformStates = m_map.getPlatformStates();
    m_savedObjectStates = m_map.getObjectStates();
}

void GameLogic::restoreState() {
    m_player1.resetPosition(m_savedPlayerPosition.x, m_savedPlayerPosition.y);
    m_player1.setVelocity(m_savedPlayerVelocity);

    m_map.setPlatformStates(m_savedPlatformStates);
    m_map.setObjectStates(m_savedObjectStates);
}

void GameLogic::pauseGame() {
    m_isGamePaused = true;
    saveState();
}

void GameLogic::resumeGame() {
    m_isGamePaused = false;
    restoreState();
}