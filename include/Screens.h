#pragma once
#include "BaseScreen.h"
#include "MenuScreen.h"
#include "PlayerSelectionScreen.h"
#include "HelpScreen.h"
#include "SettingsScreen.h"
#include "HighScoreScreen.h"
//#include "CharacterScreen.h"
#include <map>

class Screens {
public:
    Screens();
    ~Screens();
    void run();

private:
    void changeScreen(Screens_m screenType);
    void adjustWindowSize(Screens_m screenType);
    sf::RenderWindow m_window;
    BaseScreen* m_currentScreen;
    std::map<Screens_m, BaseScreen*> m_screens;
};
