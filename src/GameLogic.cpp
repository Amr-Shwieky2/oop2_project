#include "GameLogic.h"
#include <iostream>

GameLogic::GameLogic()
    : m_isGamePaused(false), m_isGameOver(false), m_score(0), m_height(0),
    m_batTimer(0), m_blackHoleTimer(0), m_heartGiftTimer(0),
    m_trampolineTimer(0), m_wingGiftTimer(0), m_sidebar(800, 50) {
    if (!m_font.loadFromFile("arial.ttf")) {
        std::cerr << "Couldn't load the font!" << std::endl;
        std::exit(-1);
    }
}

GameLogic::~GameLogic() {}

void GameLogic::initialize(sf::RenderWindow& window) {
    window.setFramerateLimit(60);
    const int platformCount = 6;
    const float gap = static_cast<float>(window.getSize().y / 2) / platformCount;

    for (int i = 0; i < platformCount; ++i) {
        float x = static_cast<float>(std::rand() % (window.getSize().x - 60));
        float y = window.getSize().y - i * gap;
        m_platforms.push_back(std::make_unique<Platform>(x, y, Platform::Type::NORMAL));
    }

    m_player.setPosition(m_platforms[1]->getBounds().left + m_platforms[1]->getBounds().width / 2 - 25,
        m_platforms[1]->getBounds().top - 50);
}

Screens_m GameLogic::handleEvents(sf::RenderWindow& window) {
    initialize(window);
    sf::Event event;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f worldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    if (m_sidebar.isPaused(static_cast<sf::Vector2i>(worldPos))) {
                        m_isGamePaused = !m_isGamePaused;
                    }
                }
            }
        }

        float deltaTime = m_clock.restart().asSeconds();
        update(deltaTime, window);
        render(window);

        if (m_isGameOver) {
            return Screens_m::HIGH_SCOORE_m;
        }
    }
    return Screens_m::GAME_m;
}

void GameLogic::update(float deltaTime, sf::RenderWindow& window) {
    if (m_isGamePaused) {
        return;
    }

    m_player.update(deltaTime);
    for (auto& platform : m_platforms) {
        platform->update(deltaTime);
    }
    for (auto& object : m_objects) {
        object->update(deltaTime);
    }

    handleCollisions();
    spawnObjects(deltaTime);
    centerView(window);
    checkGameOver();

    m_sidebar.update(m_score, static_cast<int>(m_height), m_player.getLives());
}

void GameLogic::render(sf::RenderWindow& window) {
    window.clear();

    sf::View view = window.getView();
    float viewTop = view.getCenter().y - view.getSize().y / 2;

    for (int i = 0; i < 3; ++i) {
        m_screen.setPosition(0, viewTop + i * m_screen.getTexture()->getSize().y);
        window.draw(m_screen);
    }

    m_player.draw(window);
    for (auto& platform : m_platforms) {
        platform->draw(window);
    }
    for (auto& object : m_objects) {
        object->draw(window);
    }

    window.setView(window.getDefaultView());
    m_sidebar.draw(window);

    if (m_isGameOver) {
        sf::RectangleShape scoreBackground(sf::Vector2f(300.0f, 100.0f));
        scoreBackground.setFillColor(sf::Color::Black);
        scoreBackground.setPosition(window.getView().getCenter().x - 150, window.getView().getCenter().y - 50);

        sf::Text scoreText;
        scoreText.setFont(m_font);
        scoreText.setString("Score: " + std::to_string(m_score));
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

void GameLogic::handleCollisions() {
    for (auto& object : m_objects) {
        if (object->checkCollision(m_player)) {
            object->onCollision(m_player);
            m_player.onCollision(*object);
        }
    }
    for (auto& platform : m_platforms) {
        if (platform->checkCollision(m_player)) {
            platform->onCollision(m_player);
            m_player.onCollision(*platform);
        }
    }
}

void GameLogic::spawnObjects(float deltaTime) {
    // Implement object spawning logic
}

void GameLogic::addNewPlatform(sf::RenderWindow& window) {
    float x = static_cast<float>(std::rand() % static_cast<int>(window.getSize().x - 60));
    float y = m_platforms.back()->getBounds().top - static_cast<float>(window.getSize().y / 2) / 6;
    Platform::Type type = static_cast<Platform::Type>(std::rand() % 3);

    switch (type) {
    case Platform::Type::NORMAL:
        m_platforms.push_back(std::make_unique<Platform>(x, y, Platform::Type::NORMAL));
        break;
    case Platform::Type::MOVING:
        m_platforms.push_back(std::make_unique<MovingPlatform>(x, y));
        break;
    case Platform::Type::BREAKABLE:
        m_platforms.push_back(std::make_unique<BreakablePlatform>(x, y));
        break;
    }
}

void GameLogic::centerView(sf::RenderWindow& window) {
    sf::View view = window.getView();
    view.setCenter(view.getCenter().x, m_player.getPosition().y);
    window.setView(view);
}

void GameLogic::checkGameOver() {
    if (m_player.hasFallen() || m_player.getLives() == 0) {
        m_isGameOver = true;
    }
}
