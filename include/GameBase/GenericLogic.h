#pragma once
#include "Player.h"
#include "Map.h"
#include "Sidebar.h"
#include <SFML/Graphics.hpp>


class GenericLogic
{
public:
	GenericLogic();

	void initialize(sf::RenderWindow& window, Player& player, Map& map);
	void update(float deltaTime, sf::RenderWindow& window,
		Player& player, Map& map, Sidebar& bar, bool& end);
	void CenterView(sf::RenderWindow& window, Player& player);

	void render(sf::RenderWindow& window, Player& player, Map& map, Sidebar& bar, sf::Sprite& screen);

	void saveState(sf::Vector2f& savedPlayerPosition, 
					float& savedPlayerVelocity, 
					std::vector<Map::PlatformState>& savedPlatformStates,
					std::vector<Map::ObjectState>& savedObjectStates,
					Player& player, Map& map);

	void restoreState(sf::Vector2f& savedPlayerPosition,
		float& savedPlayerVelocity,
		std::vector<Map::PlatformState>& savedPlatformStates,
		std::vector<Map::ObjectState>& savedObjectStates,
		Player& player, Map& map);


	void isFail(const Player& player, bool& end);
	void showEndBadge(sf::RenderWindow& window, const std::string& message, const bool& end);


private:
	sf::RectangleShape m_scoreBackground;
	sf::Text m_scoreText;
	sf::Font m_font;

};
