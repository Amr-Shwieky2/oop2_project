#include "Screens.h"
#include "GameException.h"
#include "TwoPlayerCharacterScreen.h"
#include "GameLogic.h"
#include "PauseScreen.h"
#include "MenuScreen.h"
#include "PlayerSelectionScreen.h"
#include "HelpScreen.h"
#include "SettingsScreen.h"
#include "HighScoreScreen.h"
#include "OnePlayerCharacterScreen.h"
#include <TwoPlayerLogic.h>

Screens::Screens() : m_firstPage(true) {
    try {
        m_screenCreators[MENU_m] = []() { return std::make_shared<MenuScreen>(); };
        m_screenCreators[PLAY_GAME_m] = []() { return std::make_shared<PlayerSelectionScreen>(); };
        m_screenCreators[HELP_m] = []() { return std::make_shared<HelpScreen>(); };
        m_screenCreators[SETTINGS_m] = []() { return std::make_shared<SettingsScreen>(); };
        m_screenCreators[HIGH_SCOORE_m] = []() { return std::make_shared<HighScoreScreen>(); };
        m_screenCreators[C1_m] = []() { return std::make_shared<OnePlayerCharacterScreen>(); };
        m_screenCreators[C2_m] = []() { return std::make_shared<TwoPlayerCharacterScreen>(); };
        m_screenCreators[GAME_m] = []() { return std::make_shared<GameLogic>(); };
        m_screenCreators[GAME_FOR_TWO_m] = []() { return std::make_shared<TwoPlayerLogic>(); };
        m_screenCreators[PAUSE_m] = []() { return std::make_shared<PauseScreen>(); };

        Singleton::instance().getSoundManager().playMusic();
        changeScreen(MENU_m);
    }
    catch (const GameException& e) {
        std::cerr << "Error initializing screens: " << e.what() << std::endl;
        throw;
    }
}

void Screens::run() {
    while (m_window.isOpen()) {
        if (m_currentScreen) {
            try {
                m_window.clear();
                m_currentScreen->render(m_window);
                m_window.display();
                Screens_m nextScreen = m_currentScreen->handleEvents(m_window);
                if (nextScreen != m_currentScreenType && m_screenCreators.find(nextScreen) != m_screenCreators.end()) {
                    changeScreen(nextScreen);
                }
            }
            catch (const GameException& e) {
                std::cerr << "Error during screen transition: " << e.what() << std::endl;
                throw;
            }
        }
    }
}

void Screens::changeScreen(Screens_m screenType) {
    try {
        adjustWindowSize(screenType);
        destroyCurrentScreen();
        m_currentScreen = m_screenCreators[screenType]();
        m_currentScreenType = screenType;

        if (screenType == GAME_m) {
            auto gameLogic = std::dynamic_pointer_cast<GameLogic>(m_currentScreen);
            gameLogic->initialize(m_window);
            Singleton::instance().setCurrentGameLogic(gameLogic);
        }
        else if (screenType == GAME_FOR_TWO_m) {
            auto gameLogic = std::dynamic_pointer_cast<TwoPlayerLogic>(m_currentScreen);
            gameLogic->initialize(m_window);
        }
    }
    catch (const GameException& e) {
        std::cerr << "Error changing screen: " << e.what() << std::endl;
        throw;
    }
}

void Screens::destroyCurrentScreen() {
    if (m_currentScreen) {
        m_currentScreen.reset();
    }
}

void Screens::adjustWindowSize(Screens_m screenType) {
    try {
        sf::Texture* texture = LoadingManager::instance().getScreen(screenType);
        if (texture) {
            sf::Vector2u imageSize = texture->getSize();
            if (m_firstPage) {
                m_window.create(sf::VideoMode(imageSize.x, imageSize.y), "Game Window");
                m_firstPage = false;
            }
            else {
                if (screenType == GAME_m && m_window.isOpen()) {
                    m_window.create(sf::VideoMode(imageSize.x, imageSize.y + 50), "Game Window");
                }
                else {
                    m_window.setSize(sf::Vector2u(imageSize.x, imageSize.y));
                    m_window.setView(sf::View(sf::FloatRect(0.f, 0.f, static_cast<float>(imageSize.x), static_cast<float>(imageSize.y))));
                }
            }
        }
    }
    catch (const GameException& e) {
        std::cerr << "Error adjusting window size: " << e.what() << std::endl;
        throw;
    }
}