#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Platform.h"
#include "MovingPlatform.h"
#include "BreakablePlatform.h"
#include "Bat.h"
#include "BlackHole.h"
#include "HeartGift.h"
#include "Trampoline.h"
#include "WingGift.h"
#include "Player.h"

class Map {
public:
    Map();
    ~Map() = default;

    void initialize(sf::RenderWindow& window);
    void update(float deltaTime, sf::RenderWindow& window, const Player& player);
    void render(sf::RenderWindow& window);
    void addNewPlatform(sf::RenderWindow& window);
    void spawnObjects(float deltaTime, sf::RenderWindow& window, const Player& player);
    void collision(Player& player, float deltaTime);

    float getHeight() const { return m_height; }
    int getScore() const { return m_score; }
    float getPlayerStartX() const { return m_playerStartX; }
    float getPlayerStartY() const { return m_playerStartY; }
   

private:
    void updatePlatform(sf::RenderWindow& window, const Player& player);
    void updateObjects(float deltaTime, sf::RenderWindow& window, const Player& player);

    std::vector<std::unique_ptr<Platform>> m_platforms;
    std::vector<std::unique_ptr<StaticObject>> m_objects;
    float m_height;
    int m_score;
    float m_batTimer;
    float m_blackHoleTimer;
    float m_giftTimer;
    float m_trampolineTimer;
    float m_wingGiftTimer;
    float m_heartGiftTimer;
    Bat m_bat;
    bool m_batActive;
    bool m_blackHoleActive;
    float m_playerStartX;
    float m_playerStartY;
};