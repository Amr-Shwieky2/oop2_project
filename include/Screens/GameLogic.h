#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Map.h"
#include "BaseScreen.h"
#include "Sidebar.h"
#include "Singleton.h"
#include "LogicBase.h"


class GameLogic : public BaseScreen, public LogicBase {
public:
    GameLogic();
    ~GameLogic() = default;

    Screens_m handleEvents(sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window) override;
   
    void initialize(sf::RenderWindow& window) override;
    void update(float deltaTime, sf::RenderWindow& window) override;

private:
    void showEndBadge(sf::RenderWindow& window) override;
    

    void saveState() override;
    void restoreState() override;

    Screens_m updateScore() override;

    
    


    
};
