#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "GameException.h"
#include "Icon.h"

const int NUM_OF_SCREENS = 7;
const int NUM_OF_HIGH_SCORES = 5;

struct high_score {
    int _score;
    std::string _name;
};

class Singleton {
public:
    static Singleton& instance();
    sf::Texture* getScreen(const int& screen);
    const std::vector<high_score>& loadHighScore();

private:
    Singleton();
    void loadTextures();

    sf::Texture m_screens[NUM_OF_SCREENS];
    std::vector<high_score> m_listScore;
};
