#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Map.h"
#include "BaseScreen.h"
#include "Sidebar.h"
#include "Singleton.h"
#include "Logic.h"

class GameLogic : public BaseScreen, public Logic {
public:
    GameLogic();
    ~GameLogic() = default;

    void initialize(sf::RenderWindow& window) override;
    Screens_m handleEvents(sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window) override;
   
    void update(float deltaTime, sf::RenderWindow& window) override;

private:
    void showEndBadge(sf::RenderWindow& window) override;
    void CenterView(sf::RenderWindow& window);
    void isFail() override;

    void saveState() override;
    void restoreState() override;

    Screens_m updateScore() override;

    
    sf::Sprite m_screen;

    Map m_map;

    
};
