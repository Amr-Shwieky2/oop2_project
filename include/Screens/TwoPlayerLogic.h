#pragma once

#include "BaseScreen.h"
#include "GameLogic.h"

class TwoPlayerLogic : public BaseScreen, public LogicBase {
public:
    TwoPlayerLogic();

    Screens_m handleEvents(sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window) override;

    void initialize(sf::RenderWindow& window) override;
    void update(float deltaTime, sf::RenderWindow& window) override;

private:
    void showEndBadge(sf::RenderWindow& window) override;

    void saveState() override;
    void restoreState() override;

    Screens_m updateScore() override;

    Player m_player2;
    Sidebar m_sidebar2;

    // Saved states for pause/resume functionality
    sf::Vector2f m_savedPlayerPosition2;
    float m_savedPlayerVelocity2;
    std::vector<Map::PlatformState> m_savedPlatformStates2;
    std::vector<Map::ObjectState> m_savedObjectStates2;
};
