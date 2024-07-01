#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "GameException.h"
#include "Icon.h"
#include "SoundManager.h"

const int NUM_OF_SCREENS = 10;
const int NUM_OF_HIGH_SCORES = 5;
const int NUM_OF_CHARACTERS = 4;
const int NUM_OF_EFFECTS = 5;

struct high_score {
    std::string _name;
    int _score;
};

class Singleton {
public:
    static Singleton& instance();
    sf::Texture* getScreen(const int& screen);
    sf::Texture* getCharacter(const int& character);
    sf::Texture* getEffect(const int& effect);
    const std::vector<high_score>& loadHighScore();
    SoundManager& getSoundManager(); // Add this method
    void updateHighScore(const std::string& playerName, int playerScore);
    void setPlayerName1(const std::string& name) { m_playerName1 = name; }
    void setPlayerName2(const std::string& name) { m_playerName2 = name; }
    std::string getPlayerName1() const { return m_playerName1; }
    std::string getPlayerName2() const { return m_playerName2; }
private:
    Singleton();
    void loadTextures();
    void loadCharacters();
    void loadEffects();

    std::string m_playerName1;
    std::string m_playerName2;
    sf::Texture m_screens[NUM_OF_SCREENS];
    sf::Texture m_charactersTexture[NUM_OF_CHARACTERS];
    sf::Texture m_effectsTexture[NUM_OF_EFFECTS];
    std::vector<high_score> m_listScore;
    SoundManager m_soundManager; // Add this member

};