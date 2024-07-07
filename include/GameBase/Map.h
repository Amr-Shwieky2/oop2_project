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

// Class to manage the game map, including platforms and objects
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

    void initialize(sf::RenderWindow& window); // Initialize platforms
    void update(float deltaTime, sf::RenderWindow& window, const Player& player); // Update platforms and objects
    void render(sf::RenderWindow& window); // Render platforms and objects
    void collision(Player& player); // Handle player collisions

    std::vector<PlatformState> getPlatformStates() const; // Get platform states for saving
    void setPlatformStates(const std::vector<PlatformState>& states); // Set platform states for loading

    std::vector<ObjectState> getObjectStates() const; // Get object states for saving
    void setObjectStates(const std::vector<ObjectState>& states); // Set object states for loading

    float getHeight() const { return m_height; }
    int getScore() const { return m_score; }
    float getPlayerStartX() const { return m_playerStartX; }
    float getPlayerStartY() const { return m_playerStartY; }

private:
    void addNewPlatform(sf::RenderWindow& window); // Add new platforms as player ascends
    void spawnObjects(float deltaTime, sf::RenderWindow& window, const Player& player); // Spawn new objects
    void updatePlatform(float deltaTime, sf::RenderWindow& window, const Player& player); // Update existing platforms
    void updateObjects(float deltaTime, sf::RenderWindow& window, const Player& player); // Update existing objects

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
