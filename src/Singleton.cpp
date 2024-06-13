#include "Singleton.h"
#include <fstream>
#include <iostream>

Singleton::Singleton() {
    loadTextures();
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

void Singleton::loadTextures() {
    try {
        if (!m_screens[MENU_m].loadFromFile("menu.jpg"))
            throw GameException("Failed to load menu.jpg");
        if (!m_screens[PLAY_GAME_m].loadFromFile("choose.jpg"))
            throw GameException("Failed to load choose.jpg");
        if (!m_screens[HELP_m].loadFromFile("help.jpg"))
            throw GameException("Failed to load help.jpg");
        if (!m_screens[SETTINGS_m].loadFromFile("setting.jpg"))
            throw GameException("Failed to load setting.jpg");
        if (!m_screens[HIGH_SCOORE_m].loadFromFile("highSccores.jpg"))
            throw GameException("Failed to load highScores.jpg");
        if (!m_screens[C1_m].loadFromFile("chooseCharacters1.jpg"))
            throw GameException("Failed to load chooseCharacters1.jpg");
        if (!m_screens[C2_m].loadFromFile("chooseCharacters2.jpg"))
            throw GameException("Failed to load chooseCharacters2.jpg");
    }
    catch (const std::exception& e) {
        std::cerr << "Error loading textures: " << e.what() << std::endl;
        throw;
    }
}

const std::vector<high_score>& Singleton::loadHighScore() {
    std::string file = "highScore.txt";
    std::ifstream input_score(file);

    if (!input_score.is_open()) {
        throw GameException("Could not open highScore.txt");
    }

    m_listScore.clear();
    while (!input_score.eof()) {
        high_score hs;
        if (!(input_score >> hs._name >> hs._score)) {
            throw GameException("Error reading high scores");
        }
        m_listScore.push_back(hs);
    }
    input_score.close();
    return m_listScore;
}
