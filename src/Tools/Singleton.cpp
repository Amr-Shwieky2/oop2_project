#include "Singleton.h"
#include <fstream>
#include <iostream>

// Constructor implementation
Singleton::Singleton() {
    try {
        // Any necessary initialization code can go here
    }
    catch (const std::exception& e) {
        std::cerr << "Error initializing Singleton: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error initializing Singleton" << std::endl;
        throw;
    }
}

// Get the singleton instance
Singleton& Singleton::instance() {
    static Singleton instance;
    return instance;
}

// Set player character 1
void Singleton::setPlayerCharacter1(const int& Character) {
    m_characterNamber1 = Character;
    fillCharacters(Character, m_playerCharacter1);
}

// Set player character 2
void Singleton::setPlayerCharacter2(const int& Character) {
    m_characterNamber2 = Character;
    fillCharacters(Character, m_playerCharacter2);
}

Characters Singleton::getPlayerCharacter1() const
{
    return m_playerCharacter1;
}

Characters Singleton::getPlayerCharacter2() const
{
    return m_playerCharacter2;
}

// Helper function to set player characters based on character index
void Singleton::fillCharacters(const int& Character, Characters& player) {
    try {
        switch (Character) {
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
        case 4:
            player = DARK_MAN_WINGS_p;
            break;
        case 5:
            player = DINASOR_WINGS_p;
            break;
        case 6:
            player = WITCH_WINGS_p;
            break;
        case 7:
            player = SHARP_WINGS_p;
            break;
        default:
            throw GameException("Invalid character index");
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error setting player character: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error setting player character" << std::endl;
        throw;
    }
}

// Set the current game logic
void Singleton::setCurrentGameLogic(std::shared_ptr<GameLogic> gameLogic) {
    try {
        m_currentGameLogic = gameLogic;
    }
    catch (const std::exception& e) {
        std::cerr << "Error setting current game logic: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error setting current game logic" << std::endl;
        throw;
    }
}

TwoPlayerLogic& Singleton::getCurrentTwoGameLogic()
{
    try {
        if (!m_currentTwoGameLogic) {
            throw GameException("Current game logic is not set");
        }
        return *m_currentTwoGameLogic;
    }
    catch (const std::exception& e) {
        std::cerr << "Error getting current game logic: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error getting current game logic" << std::endl;
        throw;
    }
}

void Singleton::setCurrentTwoGameLogic(std::shared_ptr<TwoPlayerLogic> gameLogic)
{
    try {
        m_currentTwoGameLogic = gameLogic;
    }
    catch (const std::exception& e) {
        std::cerr << "Error setting current game logic: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error setting current game logic" << std::endl;
        throw;
    }
}

// Get the current game logic
GameLogic& Singleton::getCurrentGameLogic() {
    try {
        if (!m_currentGameLogic) {
            throw GameException("Current game logic is not set");
        }
        return *m_currentGameLogic;
    }
    catch (const std::exception& e) {
        std::cerr << "Error getting current game logic: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error getting current game logic" << std::endl;
        throw;
    }
}

// Get the sound manager
SoundManager& Singleton::getSoundManager() {
    return m_soundManager;
}

// Set player name 1
void Singleton::setPlayerName1(const std::string& name) {
    try {
        m_playerName1 = name;
    }
    catch (const std::exception& e) {
        std::cerr << "Error setting player name 1: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error setting player name 1" << std::endl;
        throw;
    }
}

// Set player name 2
void Singleton::setPlayerName2(const std::string& name) {
    try {
        m_playerName2 = name;
    }
    catch (const std::exception& e) {
        std::cerr << "Error setting player name 2: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error setting player name 2" << std::endl;
        throw;
    }
}

// Get player name 1
std::string Singleton::getPlayerName1() const {
    try {
        return m_playerName1;
    }
    catch (const std::exception& e) {
        std::cerr << "Error getting player name 1: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error getting player name 1" << std::endl;
        throw;
    }
}

// Get player name 2
std::string Singleton::getPlayerName2() const {
    try {
        return m_playerName2;
    }
    catch (const std::exception& e) {
        std::cerr << "Error getting player name 2: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error getting player name 2" << std::endl;
        throw;
    }
}

// Get character number 1
int Singleton::getCharacterNamber1() const {
    return m_characterNamber1;
}

// Get character number 2
int Singleton::getCharacterNamber2() const {
    return m_characterNamber2;
}
