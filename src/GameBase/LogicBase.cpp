#include "LogicBase.h"
#include <iostream>

// Constructor to initialize the logic base
LogicBase::LogicBase()
    : m_player1(Singleton::instance().getPlayerCharacter1()),
    m_EndGame(false),
    m_isGamePaused(false),
    m_savedPlayerVelocity1(0) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    m_screen.setTexture(*(LoadingManager::instance().getScreen(GAME_m)));
}


// Pause the game
void LogicBase::pauseGame() {
    try {
        m_isGamePaused = true;
        saveState();
    }
    catch (const std::exception& e) {
        std::cerr << "Error pausing game in LogicBase: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error pausing game in LogicBase" << std::endl;
        throw;
    }
}

// Resume the game
void LogicBase::resumeGame() {
    try {
        m_isGamePaused = false;
        restoreState();
    }
    catch (const std::exception& e) {
        std::cerr << "Error resuming game in LogicBase: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error resuming game in LogicBase" << std::endl;
        throw;
    }
}
