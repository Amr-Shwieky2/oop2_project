#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Player.h"
#include "Platform.h"
#include "MovingPlatform.h"
#include "BreakablePlatform.h"
#include "Bat.h"
#include "BlackHole.h"
#include "BaseScreen.h"
#include "HeartGift.h"
#include "Trampoline.h"
#include "WingGift.h"
#include "Singleton.h"

#include "Sidebar.h"

const int MEDIUM_HEIGHT = 30;
const float BAT_SPAWN_INTERVAL = 5.0f;
const int HARD_HEIGHT = 100;
const float BLACK_HOLE_SPAWN_INTERVAL = 10.0f;
const float GIFT_SPAWN_INTERVAL = 3.0f;
const float TRAMPOLINE_SPAWN_INTERVAL = 3.0f;
const float WING_GIFT_SPAWN_INTERVAL = 3.0f;

class GameLogic : public BaseScreen {
public:
    GameLogic();
    ~GameLogic();

    void initialize(sf::RenderWindow& window);
    Screens_m handleEvents(sf::RenderWindow& window) override;
    void update(float deltaTime, sf::RenderWindow& window , float displayedHeight);
    void render(sf::RenderWindow& window) override;

private:
    void addNewPlatform(sf::RenderWindow& window);

    sf::Font m_font;
    sf::Clock m_clock;

    std::vector<Platform*> m_platforms;
    Player m_player;
    Bat m_bat;
    BlackHole m_blackHole;
    HeartGift m_heartGift;
    Trampoline m_trampoline;
    WingGift m_wingGift;
    sf::Sprite m_screen;
    bool m_isGamePaused;
    int m_score;
    bool m_batActive;
    float m_batTimer;
    float m_blackHoleTimer;
    float m_giftTimer;
    float m_trampolineTimer;
    float m_wingGiftTimer;
    float m_playerStartX;
    float m_playerStartY;

    Sidebar m_sidebar;  // Add the Sidebar instance
};
