#pragma once
#include "BaseScreen.h"
#include <iostream>
#include <map>
#include <memory>
#include <functional>
#include <SFML/Graphics.hpp>

class Screens {
public:
    Screens();
    ~Screens() = default;
    void run();

private:
    void changeScreen(Screens_m screenType);
    void adjustWindowSize(Screens_m screenType);
    void destroyCurrentScreen();

    sf::RenderWindow m_window;
    std::shared_ptr<BaseScreen> m_currentScreen;
    std::map<Screens_m, std::function<std::shared_ptr<BaseScreen>()>> m_screenCreators;
    Screens_m m_currentScreenType;
    bool m_firstPage;
};