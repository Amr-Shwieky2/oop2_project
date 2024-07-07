#pragma once

#include "BaseScreen.h"
#include "GameLogic.h"
#include "TwoPlayerSidebar.h"


class TwoPlayerLogic : public BaseScreen, public LogicBase {
public:
    TwoPlayerLogic();

    Screens_m handleEvents(sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window) override;

    void initialize(sf::RenderWindow& window) override;
    void update(float deltaTime, sf::RenderWindow& window) override;

private:
    void showEndBadge(sf::RenderWindow& window) override;
    void CenterView(sf::RenderWindow& window);
    void saveState() override;
    void restoreState() override;

    Screens_m updateScore() override;

    bool mouseEvent(sf::RenderWindow& window) override;

    Player m_player2;
    TwoPlayerSidebar m_sidebar;

    // Saved states for pause/resume functionality
    sf::Vector2f m_savedPlayerPosition2;
    float m_savedPlayerVelocity2;
    std::vector<Map::PlatformState> m_savedPlatformStates2;
    std::vector<Map::ObjectState> m_savedObjectStates2;
};
