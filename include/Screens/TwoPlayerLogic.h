#pragma once
#include "BaseScreen.h"
#include "GameLogic.h"

class TwoPlayerLogic : public BaseScreen
{
public:
    TwoPlayerLogic();

    Screens_m handleEvents(sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window) override;

private:
    sf::View m_leftView;
    sf::View m_rightView;
    sf::RectangleShape m_line;

    sf::Clock m_clock;

    GameLogic m_leftLogic;
    GameLogic m_rightLogic;

    void initializeViewsAndLine(sf::RenderWindow& window);
};