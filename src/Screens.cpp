#include "Screens.h"

Screens::Screens() : m_currentScreen(nullptr) {
    m_window.create(sf::VideoMode(800, 600), "Game Window"); // Initial size, will adjust

    m_screens[MENU_m] = new MenuScreen();
    m_screens[PLAY_GAME_m] = new PlayerSelectionScreen();
    m_screens[HELP_m] = new HelpScreen();
    m_screens[SETTINGS_m] = new SettingsScreen();
    m_screens[HIGH_SCOORE_m] = new HighScoreScreen();
  /*  m_screens[C1_m] = new CharacterScreen(C1_m);
    m_screens[C2_m] = new CharacterScreen(C2_m);*/

    changeScreen(MENU_m); // Start with the menu screen
}

Screens::~Screens() {
    for (auto& screenPair : m_screens) {
        delete screenPair.second;
    }
}

void Screens::run() {
    while (m_window.isOpen()) {
        if (m_currentScreen) {
            Screens_m nextScreen = m_currentScreen->handleEvents(m_window);
            if (m_screens.find(nextScreen) != m_screens.end()) { // Ensure valid screen transitions
                changeScreen(nextScreen);
            }
            m_window.clear();
            m_currentScreen->render(m_window);
            m_window.display();
        }
    }
}

void Screens::changeScreen(Screens_m screenType) {
    adjustWindowSize(screenType);
    m_currentScreen = m_screens[screenType];
}

void Screens::adjustWindowSize(Screens_m screenType) {
    sf::Texture* texture = Singleton::instance().getScreen(screenType);
    if (texture) {
        sf::Vector2u imageSize = texture->getSize();
        m_window.setSize(sf::Vector2u(static_cast<unsigned int>(imageSize.x), static_cast<unsigned int>(imageSize.y)));
        m_window.setView(sf::View(sf::FloatRect(0, 0, static_cast<float>(imageSize.x), static_cast<float>(imageSize.y))));
    }
}
