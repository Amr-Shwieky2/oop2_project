#include "GameLogic.h"
#include <iostream>

GameLogic::GameLogic()
    : m_bat(-100, -100),
    m_blackHole(-100, -100),
    m_heartGift(-100, -100),
    m_trampoline(-100, -100),
    m_wingGift(-100, -100),
    m_score(0),
    m_Height(0),
    m_batActive(false),
    m_batTimer(0),
    m_blackHoleTimer(0),
    m_giftTimer(0),
    m_trampolineTimer(0),
    m_wingGiftTimer(0),
    m_sidebar(800, 50),
    m_isGamePaused(false),
    m_playerStartX(0),
    m_playerStartY(0),
    m_nextScreen(GAME_m),
    m_EndGame(false),
    m_player(Singleton::instance().getPlayerCharacter1())
{
    if (!m_font.loadFromFile("arial.ttf")) {
        std::cerr << "Couldn't load the font!" << std::endl;
        std::exit(-1);
    }

    std::srand(static_cast<unsigned>(std::time(nullptr)));
    m_screen.setTexture(*(Singleton::instance().getScreen(GAME_m)));
}

GameLogic::~GameLogic() {
    for (auto platform : m_platforms) {
        delete platform;
    }
}

void GameLogic::initialize(sf::RenderWindow& window)
{

    window.setFramerateLimit(60);
    const int platformCount = 6;
    const float gap = static_cast<float>(window.getSize().y / 2) / platformCount;

    
    for (int i = 0; i < platformCount; ++i) {
        float x = static_cast<float>(std::rand() % (window.getSize().x - 60));
        float y = window.getSize().y - i * gap;
        m_platforms.push_back(new Platform(x, y));
    }

    m_playerStartX = m_platforms[0]->getBounds().left + m_platforms[0]->getBounds().width / 2 - 25;
    m_playerStartY = m_platforms[0]->getBounds().top - 100;
     m_player.resetPosition(m_playerStartX, m_playerStartY);
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
                    sf::Vector2i transformedMousePos = static_cast<sf::Vector2i>(worldPos);
                    if (m_sidebar.isPaused(transformedMousePos)) {
                        m_isGamePaused = !m_isGamePaused;  // Toggle pause state
                        std::cout << (m_isGamePaused ? "Game Paused" : "Game Resumed") << std::endl;
                    }
                }
            }
        }


        float deltaTime = m_clock.restart().asSeconds();
        m_Height = m_playerStartY - m_player.getPosition().y;
        update(deltaTime, window);
        render(window);
        if(m_EndGame) {
            //std::cout << Singleton::instance().getPlayerName1();
            //
            Singleton::instance().updateHighScore(Singleton::instance().getPlayerName1(), m_score);

            return Screens_m::HIGH_SCOORE_m;
        }


    }
    return Screens_m::GAME_m; // Adjust this return value based on your screen management logic
}

void GameLogic::levelsLogic(float deltaTime, sf::RenderWindow& window)
{
    if (m_player.getPosition().y < MEDIUM_HEIGHT) {
        m_batActive = true;
    }

    if (m_player.getPosition().y < HARD_HEIGHT) {
        m_blackHoleTimer += deltaTime;
        if (m_blackHoleTimer >= BLACK_HOLE_SPAWN_INTERVAL) {
            m_blackHoleTimer = 0;
            m_blackHole.resetPosition(static_cast<float>(std::rand() % window.getSize().x),
                static_cast<float>(m_player.getPosition().y - 350));
        }
    }

}

void GameLogic::collision()
{
    if (m_blackHole.getBounds().intersects(m_player.getBounds())) {
        //window.close();
        m_EndGame = true;
    }

    if (m_heartGift.getBounds().intersects(m_player.getBounds())) {
        m_player.increaseLife();
    }

    if (m_trampoline.getBounds().intersects(m_player.getBounds())) {
        m_player.boostJump();
    }

    if (m_wingGift.getBounds().intersects(m_player.getBounds())) {
        m_player.activateFlying(1.0f);
        m_wingGift.resetPosition(m_player.getPosition().x, m_player.getPosition().y);
    }

    if (m_bat.getBounds().intersects(m_player.getBounds())) {
        m_player.decrementLife();
    }
}

void GameLogic::update(float deltaTime, sf::RenderWindow& window)
{
    levelsLogic(deltaTime, window);

    if (m_batActive) {
        m_batTimer += deltaTime;
        if (m_batTimer >= BAT_SPAWN_INTERVAL) {
            m_batTimer = 0;
            m_bat.resetPosition(static_cast<float>(window.getSize().x), static_cast<float>(m_player.getPosition().y - 300));
        }
        m_bat.update(deltaTime);
        
    }

    m_giftTimer += deltaTime;
    if (m_giftTimer >= GIFT_SPAWN_INTERVAL || 
        m_heartGift.getBounds().intersects(m_player.getBounds())) {
        m_giftTimer = 0;
        m_heartGift.resetPosition(static_cast<float>(std::rand() % window.getSize().x),
            static_cast<float>(m_player.getPosition().y - 350));
    }

    m_trampolineTimer += deltaTime;
    if (m_trampolineTimer >= TRAMPOLINE_SPAWN_INTERVAL) {
        m_trampolineTimer = 0;
        if (!m_platforms.empty()) {
            int randomIndex = std::rand() % m_platforms.size();
            m_trampoline.resetPosition(m_platforms[randomIndex]);
        }
    }

    m_wingGiftTimer += deltaTime;
    if (m_wingGiftTimer >= WING_GIFT_SPAWN_INTERVAL) {
        m_wingGiftTimer = 0;
        m_wingGift.resetPosition(static_cast<float>(std::rand() % window.getSize().x),
                                  static_cast<float>(m_player.getPosition().y - 350));
    }

    
    collision();
    m_player.update(m_platforms, deltaTime);

    isFail();

    CenterView(window);

    
    updatePlatform(window);
    

    m_sidebar.update(m_score, static_cast<int>(m_Height), m_player.getLives());  // Update Sidebar
}

void GameLogic::isFail() 
{
    if (m_player.hasFallen() || m_player.getLives() == 0) {
        m_EndGame = true;
    }
}

void GameLogic::CenterView(sf::RenderWindow& window) 
{
    sf::View view = window.getView();
    view.setCenter(view.getCenter().x, m_player.getPosition().y);
    window.setView(view);
}

void GameLogic::updatePlatform(sf::RenderWindow& window)
{
    if (m_player.getPosition().y < m_platforms.back()->getBounds().top + 300)
    {
        addNewPlatform(window);
    }

    if (!m_platforms.empty() &&
        m_platforms[0]->getBounds().top > m_player.getPosition().y + 400) {
        delete m_platforms[0];
        m_platforms.erase(m_platforms.begin());
        m_score++;
    }

    auto it = m_platforms.begin();
    while (it != m_platforms.end()) {
        if ((*it)->isBreakable() && static_cast<BreakablePlatform*>(*it)->isBroken()) {
            delete* it;  // Free memory if you're using raw pointers
            it = m_platforms.erase(it);  // Remove from the vector
        }
        else {
            ++it;
        }
    }

    m_sidebar.update(m_score, static_cast<int>(m_Height), m_player.getLives());  // Update Sidebar
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
    m_bat.draw(window);
    m_blackHole.draw(window);
    m_heartGift.draw(window);
    m_trampoline.draw(window);
    m_wingGift.draw(window);

    for (auto platform : m_platforms) {
        platform->draw(window);
    }

    // Reset the view to the default view to draw the sidebar fixed at the top
    window.setView(window.getDefaultView());
    m_sidebar.draw(window);

    // Draw end game score if needed
    if (m_EndGame) 
    {
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
