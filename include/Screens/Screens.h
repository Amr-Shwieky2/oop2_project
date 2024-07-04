#pragma once
#include "BaseScreen.h"
#include "MenuScreen.h"
#include "PlayerSelectionScreen.h"
#include "HelpScreen.h"
#include "SettingsScreen.h"
#include "HighScoreScreen.h"
#include "OnePlayerCharacterScreen.h"
#include <map>
#include <memory>
#include <SFML/Graphics.hpp>

class Screens {
public:
    Screens();
    ~Screens() = default;
    void run();

private:
    void changeScreen(Screens_m screenType);
    void adjustWindowSize(Screens_m screenType);
    sf::RenderWindow m_window;
    std::shared_ptr<BaseScreen> m_currentScreen;
    std::map<Screens_m, std::shared_ptr<BaseScreen>> m_screens;
    Screens_m m_currentScreenType;
    bool m_firstPage;
};