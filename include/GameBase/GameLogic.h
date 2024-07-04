#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Map.h"
#include "BaseScreen.h"
#include "Sidebar.h"
#include "Singleton.h"

class GameLogic : public BaseScreen {
public:
    GameLogic();
    ~GameLogic() = default;

    void initialize(sf::RenderWindow& window);
    Screens_m handleEvents(sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window) override;
    void pauseGame();
    void resumeGame();

protected:
    void update(float deltaTime, sf::RenderWindow& window);
    void CenterView(sf::RenderWindow& window);
    void isFail();

    void saveState();
    void restoreState();

    sf::Font m_font;
    sf::Clock m_clock;

    Player m_player1;
    sf::Sprite m_screen;

    bool m_isGamePaused;
    bool m_EndGame;
    Screens_m m_nextScreen;

    Sidebar m_sidebar;
    Map m_map;

    // Saved states for pause/resume functionality
    sf::Vector2f m_savedPlayerPosition;
    float m_savedPlayerVelocity;
    float m_savedClockTime;
    std::vector<Map::PlatformState> m_savedPlatformStates;
    std::vector<Map::ObjectState> m_savedObjectStates;
};
