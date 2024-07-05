#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "GameException.h"
#include "GameObject.h"

const int NUM_OF_SCREENS = 10;
const int NUM_OF_CHARACTERS = 4;
const int NUM_OF_EFFECTS = 5;
const int NUM_OF_HIGH_SCORES = 5;

struct high_score {
    std::string _name;
    int _score;
};

class LoadingManager {
public:
    static LoadingManager& instance();
    sf::Texture* getScreen(const int& screen);
    sf::Texture* getCharacter(const int& character);
    sf::Texture* getEffect(const int& effect);
    const std::vector<high_score>& loadHighScore();
    void updateHighScore(const std::string& playerName, int playerScore);

private:
    LoadingManager();
    void loadTextures();
    void loadCharacters();
    void loadEffects();

    sf::Texture m_screens[NUM_OF_SCREENS];
    sf::Texture m_charactersTexture[NUM_OF_CHARACTERS];
    sf::Texture m_effectsTexture[NUM_OF_EFFECTS];
    std::vector<high_score> m_listScore;
};
