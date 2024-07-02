#include "Singleton.h"
#include <fstream>
#include <iostream>

void Singleton::setPlayerCharacter1(const int& Character)
{
    fillCharacters(Character, m_playerCharacter1);
}

void Singleton::setPlayerCharacter2(const int& Character)
{
    fillCharacters(Character, m_playerCharacter2);
}

Singleton::Singleton() {
    loadTextures();
    loadCharacters();
    loadEffects();
}

Singleton& Singleton::instance() {
    static Singleton instance;
    return instance;
}

sf::Texture* Singleton::getScreen(const int& screen) {
    if (screen < 0 || screen >= NUM_OF_SCREENS) {
        throw GameException("Screen index out of range");
    }
    return &m_screens[screen];
}

sf::Texture* Singleton::getCharacter(const int& character) {
    if (character < 0 || character >= NUM_OF_CHARACTERS) {
        throw GameException("character index out of range");
    }
    return &m_charactersTexture[character];
}

sf::Texture* Singleton::getEffect(const int& effect) {
    if (effect < 0 || effect >= NUM_OF_EFFECTS) {
        throw GameException("effect index out of range");
    }
    return &m_effectsTexture[effect];
}

void Singleton::loadTextures() {
    try {
        if (!m_screens[MENU_m].loadFromFile("newMenu.jpg"))
            throw GameException("Failed to load menu.jpg");
        if (!m_screens[PLAY_GAME_m].loadFromFile("newChoose.jpg"))
            throw GameException("Failed to load choose.jpg");
        if (!m_screens[HELP_m].loadFromFile("newHelp.jpg"))
            throw GameException("Failed to load help.jpg");
        if (!m_screens[SETTINGS_m].loadFromFile("setting.jpg"))
            throw GameException("Failed to load setting.jpg");
        if (!m_screens[HIGH_SCOORE_m].loadFromFile("highSccores.jpg"))
            throw GameException("Failed to load highScores.jpg");
        if (!m_screens[C1_m].loadFromFile("chooseCharacters1.jpg"))
            throw GameException("Failed to load chooseCharacters1.jpg");
        if (!m_screens[C2_m].loadFromFile("chooseCharacters2.jpg"))
            throw GameException("Failed to load chooseCharacters2.jpg");
        if (!m_screens[GAME_m].loadFromFile("background.jpg"))
            throw GameException("Failed to load background.jpg");
    }
    catch (const std::exception& e) {
        std::cerr << "Error loading textures: " << e.what() << std::endl;
        throw;
    }
}

void Singleton::loadCharacters()
{
    try
    {
        if(!m_charactersTexture[DARK_MAN_p].loadFromFile("dark.png"))
            throw GameException("Failed to load dark.png");
        if (!m_charactersTexture[DINASOR_p].loadFromFile("dinasor.png"))
            throw GameException("Failed to load dinasor.png");
        if (!m_charactersTexture[SHARP_p].loadFromFile("sharp.png"))
            throw GameException("Failed to load sharp.png");
        if (!m_charactersTexture[WITCH_p].loadFromFile("witch.png"))
            throw GameException("Failed to load witch.png");

    }
    catch (const std::exception& e)
    {
        std::cerr << "Error loading textures: " << e.what() << std::endl;
        throw;
    }
}

void Singleton::loadEffects()
{
    try
    {
        if (!m_effectsTexture[BAT_a].loadFromFile("bat.png"))
            throw GameException("Failed to load bat.png");
        if (!m_effectsTexture[HEART_a].loadFromFile("heart.png"))
            throw GameException("Failed to load heart.png");
        if (!m_effectsTexture[HOLE_a].loadFromFile("hole.png"))
            throw GameException("Failed to load hole.png");
        if (!m_effectsTexture[TRAMPOLINE_a].loadFromFile("trampoline.png"))
            throw GameException("Failed to load trampoline.png");
        if (!m_effectsTexture[WINGS_a].loadFromFile("wings.png"))
            throw GameException("Failed to load wings.png");

    }
    catch (const std::exception& e)
    {
        std::cerr << "Error loading textures: " << e.what() << std::endl;
        throw;
    }
}

void Singleton::fillCharacters(const int& Character, Characters& player)
{
    switch (Character)
    {
    case 0:
        player = DARK_MAN_p;
        break;
    case 1:
        player = DINASOR_p;
        break;
    case 2:
        player = WITCH_p;
        break;
    case 3:
        player = SHARP_p;
        break;

    default:
        break;
    }
}

const std::vector<high_score>& Singleton::loadHighScore() {
    std::string file = "highScore.txt";
    std::ifstream input_score(file);//input file 

    //checks if the file was successfully opened
    if (!input_score.is_open()) {
        throw GameException("Could not open highScore.txt");
    }

    m_listScore.clear();
    std::string name;
    int score;
    //reads pairs of values from the file
    while (input_score >> name >> score) {
        if (input_score.fail()) {
            throw GameException("Error reading high scores");
        }
        m_listScore.push_back(high_score{ name, score });
    }

    input_score.close();

    return m_listScore;
}

void Singleton::updateHighScore(const std::string& playerName, int playerScore) {
    try {
        // Load current high scores
        loadHighScore();

        // Insert new score
        m_listScore.push_back(high_score{ playerName, playerScore }); //////v

        

        // Sort the m_listScore in descending order
        std::sort(m_listScore.begin(), m_listScore.end(), [](const high_score& a, const high_score& b) {
            return a._score > b._score; // Descending order
            });

        

        // If we have more than the maximum number of high scores, remove the lowest one
        if (m_listScore.size() >= NUM_OF_HIGH_SCORES) {
            m_listScore.pop_back(); // Remove the last element, which is the lowest score due to sorting //////vvvvvv
        }

        for (const auto& hs : m_listScore) {
            std::cout << "in vector: " << hs._name << " " << hs._score << std::endl;///v
        }

        // Write updated m_listScore to file
        std::ofstream output_score("highScore.txt", std::ofstream::trunc); //  clears the existing content of the file
        if (!output_score) {
            throw GameException("Could not open highScore.txt for writing");
        }

        for (const auto& score : m_listScore) {
            output_score << score._name << " " << score._score << std::endl;
        }


        output_score.close();
    }
    catch (const std::exception& e) {
        std::cerr << "Error updating high scores: " << e.what() << std::endl;
        throw;
    }
}

SoundManager& Singleton::getSoundManager() {
    return m_soundManager;
}

