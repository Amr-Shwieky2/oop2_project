#pragma once
#include "Player.h"
#include "Map.h"
#include "Sidebar.h"
#include <SFML/Graphics.hpp>

// Class representing generic game logic
class GenericLogic {
public:
    GenericLogic();

    void initialize(sf::RenderWindow& window, Player& player, Map& map); // Initialize the game logic
    void update(float deltaTime, sf::RenderWindow& window,
        Player& player, Map& map, Sidebar& bar, bool& end); // Update the game logic
    void CenterView(sf::RenderWindow& window, Player& player); // Center the view

    void render(sf::RenderWindow& window, Player& player, Map& map, Sidebar& bar, sf::Sprite& screen); // Render the game

    void saveState(sf::Vector2f& savedPlayerPosition, float& savedPlayerVelocity,
        std::vector<Map::PlatformState>& savedPlatformStates,
        std::vector<Map::ObjectState>& savedObjectStates, Player& player, Map& map); // Save the game state

    void restoreState(sf::Vector2f& savedPlayerPosition, float& savedPlayerVelocity,
        std::vector<Map::PlatformState>& savedPlatformStates,
        std::vector<Map::ObjectState>& savedObjectStates, Player& player, Map& map); // Restore the game state

    void isFail(const Player& player, bool& end); // Check if the player has failed
    void showEndBadge(sf::RenderWindow& window, const std::string& message, const bool& end); // Show the end badge

private:
    sf::RectangleShape m_scoreBackground;
    sf::Text m_scoreText;
    sf::Font m_font;
};
