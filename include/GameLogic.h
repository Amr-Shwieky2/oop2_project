#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Player.h"
#include "Platform.h"
#include "MovingPlatform.h"
#include "BreakablePlatform.h"
#include "Bat.h"
#include "BlackHole.h"
#include "HeartGift.h"
#include "Trampoline.h"
#include "WingGift.h"
#include "Sidebar.h"
#include "BaseScreen.h"

const int MEDIUM_HEIGHT = 30;
const float BAT_SPAWN_INTERVAL = 5.0f;
const int HARD_HEIGHT = 100;
const float BLACK_HOLE_SPAWN_INTERVAL = 10.0f;
const float GIFT_SPAWN_INTERVAL = 3.0f;
const float TRAMPOLINE_SPAWN_INTERVAL = 3.0f;
const float WING_GIFT_SPAWN_INTERVAL = 9.0f;

class GameLogic : public BaseScreen {
public:
    GameLogic();
    ~GameLogic();

    void initialize(sf::RenderWindow& window);
    Screens_m handleEvents(sf::RenderWindow& window) override;

    void update(float deltaTime, sf::RenderWindow& window);
    void render(sf::RenderWindow& window) override;

private:
    void handleCollisions();
    void spawnObjects(float deltaTime);
    void addNewPlatform(sf::RenderWindow& window);
    void centerView(sf::RenderWindow& window);
    void checkGameOver();

    sf::Font m_font;
    sf::Clock m_clock;
    Player m_player;
    Sidebar m_sidebar;
    bool m_isGamePaused;
    bool m_isGameOver;
    int m_score;
    float m_height;
    float m_batTimer;
    float m_blackHoleTimer;
    float m_heartGiftTimer;
    float m_trampolineTimer;
    float m_wingGiftTimer;

    std::vector<std::unique_ptr<Collidable>> m_objects;
    std::vector<std::unique_ptr<Platform>> m_platforms;
};
