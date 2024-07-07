#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Map.h"
#include "BaseScreen.h"
#include "Sidebar.h"
#include "Singleton.h"
#include "LogicBase.h"

// Class representing the game logic
class GameLogic : public BaseScreen, public LogicBase {
public:
    GameLogic();
    ~GameLogic() = default;

    Screens_m handleEvents(sf::RenderWindow& window) override; // Handle events for the game
    void render(sf::RenderWindow& window) override; // Render the game
    void initialize(sf::RenderWindow& window) override; // Initialize the game
    void update(float deltaTime, sf::RenderWindow& window) override; // Update the game logic

private:
    void showEndBadge(sf::RenderWindow& window) override; // Show the end badge
    void saveState() override; // Save the game state
    void restoreState() override; // Restore the game state
    Screens_m updateScore() override; // Update the score
};
