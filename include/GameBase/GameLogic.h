#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
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
const float WING_GIFT_SPAWN_INTERVAL = 9.0f;

class GameLogic : public BaseScreen {
public:
    GameLogic();
    ~GameLogic() = default;

    void initialize(sf::RenderWindow& window);
    Screens_m handleEvents(sf::RenderWindow& window) override;

    

    void render(sf::RenderWindow& window) override;
private:
    void addNewPlatform(sf::RenderWindow& window);
    void spawnObjects(float deltaTime, sf::RenderWindow& window);
    void updateObjects(float deltaTime, sf::RenderWindow& window);
    void collision(float deltaTime);
    void update(float deltaTime, sf::RenderWindow& window);
    void isFail();
    void CenterView(sf::RenderWindow& window);
    void updatePlatform(sf::RenderWindow& window);

    sf::Font m_font;
    sf::Clock m_clock;
    std::vector<std::unique_ptr<Platform>> m_platforms;
    Player m_player;
    
    sf::Sprite m_screen;
    bool m_isGamePaused;
    int m_score;
    float m_Height;
    bool m_batActive;
    bool m_blackHoleActive;
    float m_batTimer;
    float m_blackHoleTimer;
    float m_giftTimer;
    float m_trampolineTimer;
    float m_wingGiftTimer;
    float m_heartGiftTimer;
    float m_playerStartX;
    float m_playerStartY;
    Screens_m m_nextScreen;

    Sidebar m_sidebar;

    bool m_EndGame;

    std::vector<std::unique_ptr<Collidable>> m_objects;

};