#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "GameException.h"
#include "GameObject.h"

// Constants for various resource counts
const int NUM_OF_SCREENS = 10;
const int NUM_OF_CHARACTERS = 8;
const int NUM_OF_EFFECTS = 5;
const int NUM_OF_HIGH_SCORES = 5;

// Struct for holding high score data
struct high_score {
    std::string _name;
    int _score;
};

// Singleton class for loading and managing game resources
class LoadingManager {
public:
    static LoadingManager& instance(); // Get the singleton instance
    sf::Texture* getScreen(const int& screen); // Get a screen texture by index
    sf::Texture* getCharacter(const int& character); // Get a character texture by index
    sf::Texture* getEffect(const int& effect); // Get an effect texture by index
    const std::vector<high_score>& loadHighScore(); // Load high scores from file
    void updateHighScore(const std::string& playerName, int playerScore); // Update high scores

private:
    LoadingManager(); // Private constructor
    void loadTextures(); // Load screen textures
    void loadCharacters(); // Load character textures
    void loadEffects(); // Load effect textures

    sf::Texture m_screens[NUM_OF_SCREENS]; // Array of screen textures
    sf::Texture m_charactersTexture[NUM_OF_CHARACTERS]; // Array of character textures
    sf::Texture m_effectsTexture[NUM_OF_EFFECTS]; // Array of effect textures
    std::vector<high_score> m_listScore; // Vector of high scores
};
