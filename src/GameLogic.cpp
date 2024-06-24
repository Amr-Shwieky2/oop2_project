#include "GameLogic.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

GameLogic::GameLogic()
    : m_bat(-100, -100),
    m_blackHole(-100, -100),
    m_score(0),
    m_batActive(false),
    m_batTimer(0),
    m_blackHoleTimer(0)
{
    
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    m_screen.setTexture(*(Singleton::instance().getScreen(GAME_m)));
    
}

GameLogic::~GameLogic() {
    for (auto platform : m_platforms) {
        delete platform;
    }
}

void GameLogic::initialize(sf::RenderWindow& window) {
    if (!m_font.loadFromFile("arial.ttf")) {
        std::cerr << "Couldn't load the font!" << std::endl;
        std::exit(-1);
    }//change to exption

    window.setFramerateLimit(60);
    const int platformCount = 6;
    const float gap = static_cast<float>(window.getSize().y / 2) / platformCount;

    for (int i = 0; i < platformCount; ++i) {
        float x = static_cast<float>(std::rand() % (window.getSize().x - 60));
        float y = window.getSize().y - i * gap;
        m_platforms.push_back(new Platform(x, y));
    }

    float playerStartX = m_platforms[1]->getBounds().left + m_platforms[1]->getBounds().width / 2 - 25;
    float playerStartY = m_platforms[1]->getBounds().top - 50;
    m_player.setPosition(playerStartX, playerStartY);
}

Screens_m GameLogic::handleEvents(sf::RenderWindow& window) {
    initialize(window);
    sf::Event event;
    while (window.isOpen())
    {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
           
            
        }
        float deltaTime = m_clock.restart().asSeconds();
        update(deltaTime, window);
        render(window);
    }

    return Screens_m::GAME_m; // Adjust this return value based on your screen management logic
}

void GameLogic::update(float deltaTime, sf::RenderWindow& window) {
    if (m_player.getPosition().y < MEDIUM_HEIGHT)
        m_batActive = true;

    if (m_batActive) {
        m_batTimer += deltaTime;
        if (m_batTimer >= BAT_SPAWN_INTERVAL + 7.0f) {
            m_batTimer = 0;
            m_bat.resetPosition(static_cast<float>(window.getSize().x), static_cast<float>(m_player.getPosition().y - 300));
        }
        m_bat.update(deltaTime);
        if (m_bat.getGlobalBounds().intersects(m_player.getGlobalBounds())) {
            m_player.decrementLife();
        }
        else if (m_player.isColliding()) {
            m_player.resetCollisionFlag();
        }
    }

    if (m_player.getPosition().y < HARD_HEIGHT) {
        m_blackHoleTimer += deltaTime;
        if (m_blackHoleTimer >= BLACK_HOLE_SPAWN_INTERVAL) {
            m_blackHoleTimer = 0;
            m_blackHole.resetPosition(static_cast<float>(std::rand() % window.getSize().x),
                                        static_cast<float>(m_player.getPosition().y - 350));

        }
    }

    if (m_blackHole.getGlobalBounds().intersects(m_player.getGlobalBounds())) {
        window.close();
    }

    m_player.update(m_platforms, deltaTime);

    if (m_player.hasFallen()) {
        window.close();
    }

    sf::View view = window.getView();
    view.setCenter(view.getCenter().x, m_player.getPosition().y);
    window.setView(view);

    if (m_player.getPosition().y < m_platforms.back()->getBounds().top + 200) {
        addNewPlatform(window);
    }

    if (!m_platforms.empty() && m_platforms[0]->getBounds().top > m_player.getPosition().y + 400) {
        delete m_platforms[0];
        m_platforms.erase(m_platforms.begin());
        m_score++;
    }
}

void GameLogic::render(sf::RenderWindow& window) {
    window.clear();

    sf::View view = window.getView();
    float viewTop = view.getCenter().y - view.getSize().y / 2;

    // Draw multiple backgrounds
    for (int i = 0; i < 3; ++i) { // Adjust the number of backgrounds based on your game's needs
        m_screen.setPosition(0, viewTop + i * m_screen.getTexture()->getSize().y);
        window.draw(m_screen);

        // Draw the extra background above the current one
        if (i > 0) {
            m_screen.setTexture(*(Singleton::instance().getScreen(GAME_m)));
            m_screen.setPosition(0, viewTop + (i - 1) * m_screen.getTexture()->getSize().y);
            window.draw(m_screen);
        }
    }

    m_player.draw(window);
    m_bat.draw(window);
    m_blackHole.draw(window);
    for (auto platform : m_platforms) {
        platform->draw(window);
    }
    

    sf::Text text;
    text.setFont(m_font);
    text.setString(std::to_string(m_score));
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setPosition(window.getSize().x / 2.0f, m_player.getPosition().y - 150);
    window.draw(text);

    window.display();
}

void GameLogic::addNewPlatform(sf::RenderWindow& window) {
    float x = static_cast<float>(std::rand() % static_cast<int>(window.getSize().x - 60));
    float y = m_platforms.back()->getBounds().top - static_cast<float>(window.getSize().y / 2) / 6;
    Platform::Type type = static_cast<Platform::Type>(std::rand() % 3);

    switch (type) {
    case Platform::Type::NORMAL:
        m_platforms.push_back(new Platform(x, y));
        break;
    case Platform::Type::MOVING:
        m_platforms.push_back(new MovingPlatform(x, y));
        break;
    case Platform::Type::BREAKABLE:
        m_platforms.push_back(new BreakablePlatform(x, y));
        break;
    }
}
