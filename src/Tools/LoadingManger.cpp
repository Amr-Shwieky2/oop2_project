#include "LoadingManager.h"
#include <fstream>
#include <iostream>

// Constructor implementation
LoadingManager::LoadingManager() {
    try {
        loadTextures();
        loadCharacters();
        loadEffects();
    }
    catch (const std::exception& e) {
        std::cerr << "Error initializing LoadingManager: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error initializing LoadingManager" << std::endl;
        throw;
    }
}

// Get the singleton instance
LoadingManager& LoadingManager::instance() {
    static LoadingManager instance;
    return instance;
}

// Get a screen texture by index
sf::Texture* LoadingManager::getScreen(const int& screen) {
    if (screen < 0 || screen >= NUM_OF_SCREENS) {
        throw GameException("Screen index out of range");
    }
    return &m_screens[screen];
}

// Get a character texture by index
sf::Texture* LoadingManager::getCharacter(const int& character) {
    if (character < 0 || character >= NUM_OF_CHARACTERS) {
        throw GameException("Character index out of range");
    }
    return &m_charactersTexture[character];
}

// Get an effect texture by index
sf::Texture* LoadingManager::getEffect(const int& effect) {
    if (effect < 0 || effect >= NUM_OF_EFFECTS) {
        throw GameException("Effect index out of range");
    }
    return &m_effectsTexture[effect];
}

// Load screen textures
void LoadingManager::loadTextures() {
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
        if (!m_screens[GAME_FOR_TWO_m].loadFromFile("background.jpg"))
            throw GameException("Failed to load background.jpg");
        if (!m_screens[PAUSE_m].loadFromFile("pause.jpg"))
            throw GameException("Failed to load pause.jpg");
    }
    catch (const std::exception& e) {
        std::cerr << "Error loading textures: " << e.what() << std::endl;
        throw;
    }
}

// Load character textures
void LoadingManager::loadCharacters() {
    try {
        if (!m_charactersTexture[DARK_MAN_p].loadFromFile("dark.png"))
            throw GameException("Failed to load dark.png");
        if (!m_charactersTexture[DINASOR_p].loadFromFile("dinasor.png"))
            throw GameException("Failed to load dinasor.png");
        if (!m_charactersTexture[SHARP_p].loadFromFile("sharp.png"))
            throw GameException("Failed to load sharp.png");
        if (!m_charactersTexture[WITCH_p].loadFromFile("witch.png"))
            throw GameException("Failed to load witch.png");
        if (!m_charactersTexture[DARK_MAN_WINGS_p].loadFromFile("dark-wing.png"))
            throw GameException("Failed to load dark-wing.png");
        if (!m_charactersTexture[DINASOR_WINGS_p].loadFromFile("dinasor-wing.png"))
            throw GameException("Failed to load dinasor-wing.png");
        if (!m_charactersTexture[SHARP_WINGS_p].loadFromFile("sharp-wing.png"))
            throw GameException("Failed to load sharp-wing.png");
        if (!m_charactersTexture[WITCH_WINGS_p].loadFromFile("witch-wing.png"))
            throw GameException("Failed to load witch-wing.png");
    }
    catch (const std::exception& e) {
        std::cerr << "Error loading character textures: " << e.what() << std::endl;
        throw;
    }
}

// Load effect textures
void LoadingManager::loadEffects() {
    try {
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
    catch (const std::exception& e) {
        std::cerr << "Error loading effect textures: " << e.what() << std::endl;
        throw;
    }
}

// Load high scores from file
const std::vector<high_score>& LoadingManager::loadHighScore() {
    std::string file = "highScore.txt";
    std::ifstream input_score(file);

    if (!input_score.is_open()) {
        throw GameException("Could not open highScore.txt");
    }

    m_listScore.clear();
    std::string name;
    int score;

    while (input_score >> name >> score) {
        if (input_score.fail()) {
            throw GameException("Error reading high scores");
        }
        m_listScore.push_back(high_score{ name, score });
    }

    input_score.close();
    return m_listScore;
}

// Update high scores
void LoadingManager::updateHighScore(const std::string& playerName, int playerScore) {
    try {
        loadHighScore();
        m_listScore.push_back(high_score{ playerName, playerScore });

        std::sort(m_listScore.begin(), m_listScore.end(), [](const high_score& a, const high_score& b) {
            return a._score > b._score;
            });

        if (m_listScore.size() > NUM_OF_HIGH_SCORES) {
            m_listScore.pop_back();
        }

        std::ofstream output_score("highScore.txt", std::ofstream::trunc);
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
