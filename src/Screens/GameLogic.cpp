#include "GameLogic.h"
#include <iostream>

// Constructor to initialize the game logic
GameLogic::GameLogic() {}

// Initialize the game
void GameLogic::initialize(sf::RenderWindow& window) {
    try {
        m_logic.initialize(window, m_player1, m_map);
    }
    catch (const std::exception& e) {
        std::cerr << "Error initializing GameLogic: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error initializing GameLogic" << std::endl;
        throw;
    }
}

// Handle events for the game
Screens_m GameLogic::handleEvents(sf::RenderWindow& window) {
    try {
        m_player1.setTexture(Singleton::instance().getPlayerCharacter1());
        while (window.isOpen()) {
            if (mouseEvent(window)) return PAUSE_m;

            float deltaTime = m_clock.restart().asSeconds();
            if (!m_isGamePaused) {
                update(deltaTime, window);
            }
            render(window);
            if (m_EndGame) {
                showEndBadge(window);
                return updateScore();
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error handling events in GameLogic: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error handling events in GameLogic" << std::endl;
        throw;
    }
    return Screens_m::GAME_m;
}

// Update the game logic
void GameLogic::update(float deltaTime, sf::RenderWindow& window) {
    try {
        m_player1.update(deltaTime, sf::Keyboard::Left, sf::Keyboard::Right);
        m_logic.update(deltaTime, window, m_player1, m_map, m_sidebar, m_EndGame);
    }
    catch (const std::exception& e) {
        std::cerr << "Error updating GameLogic: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error updating GameLogic" << std::endl;
        throw;
    }
}

// Render the game
void GameLogic::render(sf::RenderWindow& window) {
    try {
        m_logic.render(window, m_player1, m_map, m_sidebar, m_screen);
    }
    catch (const std::exception& e) {
        std::cerr << "Error rendering GameLogic: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error rendering GameLogic" << std::endl;
        throw;
    }
}

// Show the end badge
void GameLogic::showEndBadge(sf::RenderWindow& window) {
    try {
        m_logic.showEndBadge(window, "Score: " + std::to_string(m_map.getScore()), m_EndGame);
    }
    catch (const std::exception& e) {
        std::cerr << "Error showing end badge in GameLogic: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error showing end badge in GameLogic" << std::endl;
        throw;
    }
}

// Save the game state
void GameLogic::saveState() {
    try {
        m_logic.saveState(m_savedPlayerPosition1, m_savedPlayerVelocity1,
            m_savedPlatformStates1, m_savedObjectStates1, m_player1, m_map);
    }
    catch (const std::exception& e) {
        std::cerr << "Error saving state in GameLogic: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error saving state in GameLogic" << std::endl;
        throw;
    }
}

// Restore the game state
void GameLogic::restoreState() {
    try {
        m_logic.restoreState(m_savedPlayerPosition1, m_savedPlayerVelocity1,
            m_savedPlatformStates1, m_savedObjectStates1, m_player1, m_map);
    }
    catch (const std::exception& e) {
        std::cerr << "Error restoring state in GameLogic: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error restoring state in GameLogic" << std::endl;
        throw;
    }
}

// Update the score
Screens_m GameLogic::updateScore() {
    try {
        LoadingManager::instance().updateHighScore(Singleton::instance().getPlayerName1(), m_map.getScore());
    }
    catch (const std::exception& e) {
        std::cerr << "Error updating score in GameLogic: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error updating score in GameLogic" << std::endl;
        throw;
    }
    return Screens_m::HIGH_SCOORE_m;
}
