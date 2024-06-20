#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "Platform.h"
#include "MovingPlatform.h"
#include "BreakablePlatform.h"
#include "Bat.h"
#include "BlackHole.h"
#include "BaseScreen.h"

const int MEDIUM_HEIGHT = 30;
const float BAT_SPAWN_INTERVAL = 5.0f;
const int HARD_HEIGHT = 100;
const float BLACK_HOLE_SPAWN_INTERVAL = 10.0f;

class GameLogic : public BaseScreen {
public:
    GameLogic();
    ~GameLogic();

    void initialize(sf::RenderWindow& window);

    Screens_m handleEvents(sf::RenderWindow& window) override;
    void update(float deltaTime, sf::RenderWindow& window);
    void render(sf::RenderWindow& window) override;


private:
    void addNewPlatform(sf::RenderWindow& window);

    sf::Font m_font;
    sf::Clock m_clock;

    std::vector<Platform*> m_platforms;
    Player m_player;
    Bat m_bat;
    BlackHole m_blackHole;

    int m_score;
    bool m_batActive;
    float m_batTimer;
    float m_blackHoleTimer;

   
};
