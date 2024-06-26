#include "Singleton.h"
#include <fstream>
#include <iostream>

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

SoundManager& Singleton::getSoundManager() {
    return m_soundManager;
}

