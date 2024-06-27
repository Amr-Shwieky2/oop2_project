#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "GameException.h"
#include "SoundManager.h"
#include "GameObject.h"

const int NUM_OF_SCREENS = 8;
const int NUM_OF_HIGH_SCORES = 5;
const int NUM_OF_CHARACTERS = 4;
const int NUM_OF_EFFECTS = 5;

struct HighScore {
    std::string name;
    int score;
};

class Singleton {
public:
    static Singleton& instance();
    sf::Texture* getScreen(int screen);
    sf::Texture* getCharacter(int character);
    sf::Texture* getEffect(int effect);
    const std::vector<HighScore>& loadHighScore();
    void updateHighScore(const std::string& playerName, int playerScore);
    SoundManager& getSoundManager();
    void setPlayerName1(const std::string& name);
    void setPlayerName2(const std::string& name);
    std::string getPlayerName1() const;
    std::string getPlayerName2() const;

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
    std::vector<HighScore> m_highScores;
    SoundManager m_soundManager;
};
