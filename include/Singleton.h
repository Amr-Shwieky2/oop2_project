#pragma once
#include <vector>
#include <fstream>
#include <memory>
#include <string>
#include <iostream>

#include "Icon.h"

const int NUM_OF_SCREENS = 7;
const int NUM_OF_HIGH_SCCORES = 5;

struct high_score {
	int _score;
	std::string _name;
};

class Singleton
{
public:
	static Singleton& instance();
	sf::Texture* getScreen(const int& screen);

	const std::vector<high_score>& loadHighScore();

	
private:
	Singleton();
	
	sf::Texture m_Screeens[NUM_OF_SCREENS];
	std::vector<high_score> m_listScore;
};

