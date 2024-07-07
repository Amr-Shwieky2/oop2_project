#pragma once
#include "BaseScreen.h"
#include <iostream>
#include <map>
#include <memory>
#include <functional>
#include <SFML/Graphics.hpp>
#include <functional>

// Class managing different screens in the game
class Screens {
public:
    Screens();
    ~Screens() = default;
    void run(); // Main loop to run the current screen

private:
    void changeScreen(Screens_m screenType); // Change the current screen
    void adjustWindowSize(Screens_m screenType); // Adjust the window size based on the screen
    void destroyCurrentScreen(); // Destroy the current screen

    sf::RenderWindow m_window; // The main game window
    std::shared_ptr<BaseScreen> m_currentScreen; // Pointer to the current screen
    std::map<Screens_m, std::function<std::shared_ptr<BaseScreen>()>> m_screenCreators; // Map of screen creators
    Screens_m m_currentScreenType; // Current screen type
    bool m_firstPage; // Flag to check if it's the first page
};
