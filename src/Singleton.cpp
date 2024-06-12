#include "Singleton.h"

Singleton::Singleton()
{
	
	m_Screeens[MENU_m].loadFromFile("menu.jpg");
	m_Screeens[PLAY_GAME_m].loadFromFile("choose.jpg");
	m_Screeens[HELP_m].loadFromFile("help.jpg");
	m_Screeens[SETTINGS_m].loadFromFile("setting.jpg");
	m_Screeens[HIGH_SCOORE_m].loadFromFile("highSccores.jpg");
	m_Screeens[C1_m].loadFromFile("chooseCharacters1.jpg");
	m_Screeens[C2_m].loadFromFile("chooseCharacters2.jpg");

	
}

Singleton& Singleton::instance()
{
	static Singleton instance;
	return instance;
}

sf::Texture* Singleton::getScreen(const int& screen)
{
	return &m_Screeens[screen];
}

const std::vector<high_score>& Singleton::loadHighScore()
{
	std::string file = "highScore.txt";
	std::ifstream input_score;
	input_score.open(file);

	if (!input_score.is_open())
	{
		std::cerr << "could not open file\n";
		exit(EXIT_FAILURE);
	}


	m_listScore.clear();
	while (!input_score.eof())
	{
		m_listScore.push_back(high_score());
		input_score >> m_listScore.back()._name;
		input_score >> m_listScore.back()._score;
	}
	input_score.close();
	return m_listScore;
}

