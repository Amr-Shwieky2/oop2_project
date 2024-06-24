#include "Screens.h"
#include <iostream>
#include "GameException.h"
#include "TwoPlayerCharacterScreen.h"
#include "GameLogic.h"

Screens::Screens() : m_currentScreen(nullptr), m_firstPage(true) {

    try {
        m_screens[MENU_m] = new MenuScreen();
        m_screens[PLAY_GAME_m] = new PlayerSelectionScreen();
        m_screens[HELP_m] = new HelpScreen();
        m_screens[SETTINGS_m] = new SettingsScreen();
        m_screens[HIGH_SCOORE_m] = new HighScoreScreen();
        m_screens[C1_m] = new CharacterScreen(C1_m);
        m_screens[C2_m] = new TwoPlayerCharacterScreen(C2_m);
        m_screens[GAME_m] = new GameLogic();
        Singleton::instance().getSoundManager().playMusic(); // Start background music
        
        changeScreen(MENU_m); // Start with the menu screen
    }
    catch (const GameException& e) {
        std::cerr << "Error initializing screens: " << e.what() << std::endl;
        throw;
    }
}

Screens::~Screens() {
    for (auto& screenPair : m_screens) {
        delete screenPair.second;
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
                if (m_screens.find(nextScreen) != m_screens.end()) { // Ensure valid screen transitions
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
            }else{
                m_window.setSize(sf::Vector2u(static_cast<unsigned int>(imageSize.x), static_cast<unsigned int>(imageSize.y)));
                m_window.setView(sf::View(sf::FloatRect(0, 0, static_cast<float>(imageSize.x), static_cast<float>(imageSize.y))));
        
            }
        }
    }
    catch (const GameException& e) {
        std::cerr << "Error adjusting window size: " << e.what() << std::endl;
        throw;
    }
}
