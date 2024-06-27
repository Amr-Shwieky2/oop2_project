#include "Singleton.h"
#include <fstream>
#include <iostream>
#include <algorithm>

Singleton::Singleton() {
    loadTextures();
    loadCharacters();
    loadEffects();
}

Singleton& Singleton::instance() {
    static Singleton instance;
    return instance;
}

sf::Texture* Singleton::getScreen(int screen) {
    if (screen < 0 || screen >= NUM_OF_SCREENS) {
        throw GameException("Screen index out of range");
    }
    return &m_screens[screen];
}

sf::Texture* Singleton::getCharacter(int character) {
    if (character < 0 || character >= NUM_OF_CHARACTERS) {
        throw GameException("Character index out of range");
    }
    return &m_charactersTexture[character];
}

sf::Texture* Singleton::getEffect(int effect) {
    if (effect < 0 || effect >= NUM_OF_EFFECTS) {
        throw GameException("Effect index out of range");
    }
    return &m_effectsTexture[effect];
}

void Singleton::loadTextures() {
    try {
        if (!m_screens[MENU_m].loadFromFile("menu.jpg")) throw GameException("Failed to load menu.jpg");
        if (!m_screens[PLAY_GAME_m].loadFromFile("choose.jpg")) throw GameException("Failed to load choose.jpg");
        if (!m_screens[HELP_m].loadFromFile("help.jpg")) throw GameException("Failed to load help.jpg");
        if (!m_screens[SETTINGS_m].loadFromFile("setting.jpg")) throw GameException("Failed to load setting.jpg");
        if (!m_screens[HIGH_SCOORE_m].loadFromFile("highScores.jpg")) throw GameException("Failed to load highScores.jpg");
        if (!m_screens[C1_m].loadFromFile("chooseCharacters1.jpg")) throw GameException("Failed to load chooseCharacters1.jpg");
        if (!m_screens[C2_m].loadFromFile("chooseCharacters2.jpg")) throw GameException("Failed to load chooseCharacters2.jpg");
        if (!m_screens[GAME_m].loadFromFile("background.jpg")) throw GameException("Failed to load background.jpg");
    }
    catch (const std::exception& e) {
        std::cerr << "Error loading textures: " << e.what() << std::endl;
        throw;
    }
}

void Singleton::loadCharacters() {
    try {
        if (!m_charactersTexture[DARK_MAN_p].loadFromFile("dark.png")) throw GameException("Failed to load dark.png");
        if (!m_charactersTexture[DINASOR_p].loadFromFile("dinasor.png")) throw GameException("Failed to load dinasor.png");
        if (!m_charactersTexture[SHARP_p].loadFromFile("sharp.png")) throw GameException("Failed to load sharp.png");
        if (!m_charactersTexture[WITCH_p].loadFromFile("witch.png")) throw GameException("Failed to load witch.png");
    }
    catch (const std::exception& e) {
        std::cerr << "Error loading character textures: " << e.what() << std::endl;
        throw;
    }
}

void Singleton::loadEffects() {
    try {
        if (!m_effectsTexture[BAT_a].loadFromFile("bat.png")) throw GameException("Failed to load bat.png");
        if (!m_effectsTexture[HEART_a].loadFromFile("heart.png")) throw GameException("Failed to load heart.png");
        if (!m_effectsTexture[HOLE_a].loadFromFile("hole.png")) throw GameException("Failed to load hole.png");
        if (!m_effectsTexture[TRAMPOLINE_a].loadFromFile("trampoline.png")) throw GameException("Failed to load trampoline.png");
        if (!m_effectsTexture[WINGS_a].loadFromFile("wings.png")) throw GameException("Failed to load wings.png");
    }
    catch (const std::exception& e) {
        std::cerr << "Error loading effect textures: " << e.what() << std::endl;
        throw;
    }
}

const std::vector<HighScore>& Singleton::loadHighScore() {
    try {
        std::ifstream inputFile("highScore.txt");
        if (!inputFile.is_open()) {
            throw GameException("Could not open highScore.txt");
        }

        m_highScores.clear();
        std::string name;
        int score;
        while (inputFile >> name >> score) {
            if (inputFile.fail()) {
                throw GameException("Error reading high scores");
            }
            m_highScores.emplace_back(HighScore{ name, score });
        }

        inputFile.close();
        return m_highScores;
    }
    catch (const std::exception& e) {
        std::cerr << "Error loading high scores: " << e.what() << std::endl;
        throw;
    }
}

void Singleton::updateHighScore(const std::string& playerName, int playerScore) {
    try {
        loadHighScore();
        m_highScores.push_back({ playerName, playerScore });

        std::sort(m_highScores.begin(), m_highScores.end(), [](const HighScore& a, const HighScore& b) {
            return a.score > b.score;
            });

        if (m_highScores.size() > NUM_OF_HIGH_SCORES) {
            m_highScores.pop_back();
        }

        std::ofstream outputFile("highScore.txt", std::ofstream::trunc);
        if (!outputFile.is_open()) {
            throw GameException("Could not open highScore.txt for writing");
        }

        for (const auto& score : m_highScores) {
            outputFile << score.name << " " << score.score << std::endl;
        }

        outputFile.close();
    }
    catch (const std::exception& e) {
        std::cerr << "Error updating high scores: " << e.what() << std::endl;
        throw;
    }
}

SoundManager& Singleton::getSoundManager() {
    return m_soundManager;
}

void Singleton::setPlayerName1(const std::string& name) {
    m_playerName1 = name;
}

void Singleton::setPlayerName2(const std::string& name) {
    m_playerName2 = name;
}

std::string Singleton::getPlayerName1() const {
    return m_playerName1;
}

std::string Singleton::getPlayerName2() const {
    return m_playerName2;
}
