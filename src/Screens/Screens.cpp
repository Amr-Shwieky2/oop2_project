#include "Screens.h"
#include "GameException.h"
#include "TwoPlayerCharacterScreen.h"
#include "GameLogic.h"
#include <iostream>

Screens::Screens() : m_firstPage(true) {
    try {
        m_screens[MENU_m] = std::make_shared<MenuScreen>();
        m_screens[PLAY_GAME_m] = std::make_shared<PlayerSelectionScreen>();
        m_screens[HELP_m] = std::make_shared<HelpScreen>();
        m_screens[SETTINGS_m] = std::make_shared<SettingsScreen>();
        m_screens[HIGH_SCOORE_m] = std::make_shared<HighScoreScreen>();
        m_screens[C1_m] = std::make_shared<OnePlayerCharacterScreen>();
        m_screens[C2_m] = std::make_shared<TwoPlayerCharacterScreen>();
        m_screens[GAME_m] = std::make_shared<GameLogic>();
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
                if (m_screens.find(nextScreen) != m_screens.end()) {
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
        m_currentScreen = m_screens[screenType];
    }
    catch (const GameException& e) {
        std::cerr << "Error changing screen: " << e.what() << std::endl;
        throw;
    }
}

void Screens::adjustWindowSize(Screens_m screenType) {
    try {
        sf::Texture* texture = Singleton::instance().getScreen(screenType);
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
                m_window.setSize(sf::Vector2u(imageSize.x, imageSize.y));
                m_window.setView(sf::View(sf::FloatRect(0.f, 0.f, static_cast<float>(imageSize.x), static_cast<float>(imageSize.y))));
            }
        }
    }
    catch (const GameException& e) {
        std::cerr << "Error adjusting window size: " << e.what() << std::endl;
        throw;
    }
}