#include "LogicBase.h"
#include <iostream>

// Constructor to initialize the logic base
LogicBase::LogicBase()
    : m_player1(Singleton::instance().getPlayerCharacter1()),
    m_sidebar(800, 50),
    m_EndGame(false),
    m_isGamePaused(false),
    m_savedPlayerVelocity1(0) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    m_screen.setTexture(*(LoadingManager::instance().getScreen(GAME_m)));
}

// Handle mouse events
bool LogicBase::mouseEvent(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f worldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                sf::Vector2i transformedMousePos = static_cast<sf::Vector2i>(worldPos);
                if (m_sidebar.isPaused(transformedMousePos)) {
                    Singleton::instance().getSoundManager().playSound("click");
                    pauseGame();
                    return true;
                }
            }
        }
    }
    return false;
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
