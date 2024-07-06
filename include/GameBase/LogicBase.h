#pragma once
#include <Player.h>
#include <Sidebar.h>
#include <Map.h>
#include "GenericLogic.h"


class LogicBase
{
public:
    LogicBase();
    virtual ~LogicBase() = default;

    bool mouseEvent(sf::RenderWindow& window);
    void pauseGame();
    void resumeGame();

    virtual void initialize(sf::RenderWindow& window) = 0;
    virtual void update(float deltaTime, sf::RenderWindow& window) = 0;


protected:
    virtual void saveState() = 0;
    virtual void restoreState() = 0;
    virtual void showEndBadge(sf::RenderWindow& window) = 0;
    virtual Screens_m updateScore() = 0;

    GenericLogic m_logic;
    

    Player m_player1;
    Sidebar m_sidebar;
    Map m_map;


    sf::Clock m_clock;
    sf::Sprite m_screen;


    bool m_isGamePaused;
    bool m_EndGame;

    

    // Saved states for pause/resume functionality
    sf::Vector2f m_savedPlayerPosition1;
    float m_savedPlayerVelocity1;
    std::vector<Map::PlatformState> m_savedPlatformStates1;
    std::vector<Map::ObjectState> m_savedObjectStates1;

   
};

