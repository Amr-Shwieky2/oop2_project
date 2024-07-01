#pragma once
#include "BaseScreen.h"
#include "MenuScreen.h"
#include "PlayerSelectionScreen.h"
#include "HelpScreen.h"
#include "SettingsScreen.h"
#include "HighScoreScreen.h"
#include "CharacterScreen.h"
#include "TwoPlayerCharacterScreen.h"
#include "PauseScreen.h"
#include "GameLogic.h"
#include <map>
#include <SFML/Graphics.hpp>

class Screens {
public:
    Screens();
    ~Screens();
    void run();
    void changeScreen(Screens_m screenType);
private:
    void adjustWindowSize(Screens_m screenType);
    sf::RenderWindow m_window;
    BaseScreen* m_currentScreen;
    std::map<Screens_m, BaseScreen*> m_screens;
    Screens_m m_currentScreenType; // Store the current screen type
    bool m_firstPage;
    sf::Sprite m_backgroundSprite; // Add this line
};
