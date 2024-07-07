#pragma once
#include <SFML/Graphics.hpp>
#include "Singleton.h"
#include "LoadingManager.h"

// Abstract base class for all game screens
class BaseScreen {
public:
    virtual ~BaseScreen() = default;

    // Handle events for the screen
    virtual Screens_m handleEvents(sf::RenderWindow& window) = 0;

    // Render the screen
    virtual void render(sf::RenderWindow& window) = 0;
};
