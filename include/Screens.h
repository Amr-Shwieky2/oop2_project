#pragma once

#include "Singleton.h"
#include <SFML/Graphics.hpp>
#include <map>


class Screens
{
public:
	Screens();
	~Screens();
	void runMenu();

private:
	void directorScreens(const Screens_m& screen, const std::string& title);
	void render(const Screens_m& screen);

	void getUpdatedScore();
	Menu_c getMenuButton(sf::Vector2i mousePos);

	void choosePlayer();
	Chooseen getChooseButton(sf::Vector2i mousePos);

	void helpPage();
	void settingsPage();
	void highScorePage();
	void chooseCharacter();

	void playerDetails(const int& numberOfPlayers);

	sf::RenderWindow m_window;

	sf::Sprite m_screens[NUM_OF_SCREENS];
	int m_TopScore[NUM_OF_HIGH_SCCORES];

	bool m_back;


};

