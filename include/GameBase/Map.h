#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Platform.h"
#include "MovingPlatform.h"
#include "BreakablePlatform.h"
#include "MovingBreakablePlatform.h"
#include "Bat.h"
#include "BlackHole.h"
#include "HeartGift.h"
#include "Trampoline.h"
#include "WingGift.h"
#include "Player.h"

class Map {
public:
    struct PlatformState {
        sf::Vector2f position;
        Platform::Type type;
        bool isBroken;
    };

    struct ObjectState {
        sf::Vector2f position;
        std::string type;
    };

    Map();
    ~Map() = default;

    void initialize(sf::RenderWindow& window);
    void update(float deltaTime, sf::RenderWindow& window, const Player& player);
    void render(sf::RenderWindow& window);
    void collision(Player& player, float deltaTime);

    std::vector<PlatformState> getPlatformStates() const;
    void setPlatformStates(const std::vector<PlatformState>& states);

    std::vector<ObjectState> getObjectStates() const;
    void setObjectStates(const std::vector<ObjectState>& states);

    float getHeight() const { return m_height; }
    int getScore() const { return m_score; }
    float getPlayerStartX() const { return m_playerStartX; }
    float getPlayerStartY() const { return m_playerStartY; }
private:
    void addNewPlatform(sf::RenderWindow& window);
    void spawnObjects(float deltaTime, sf::RenderWindow& window, const Player& player);
    void updatePlatform(float deltaTime, sf::RenderWindow& window, const Player& player);
    void updateObjects(float deltaTime, sf::RenderWindow& window, const Player& player);

    std::vector<std::unique_ptr<Platform>> m_platforms;
    std::vector<std::unique_ptr<GameObject>> m_objects;
    Bat m_bat;

    int m_score;
    float m_height;

    // Timers for spawning objects
    float m_batTimer;
    float m_blackHoleTimer;
    float m_giftTimer;
    float m_trampolineTimer;
    float m_wingGiftTimer;
    float m_heartGiftTimer;

    bool m_batActive;
    bool m_blackHoleActive;

    // Initial player start position
    float m_playerStartX;
    float m_playerStartY;

    int m_platformCount;
};
