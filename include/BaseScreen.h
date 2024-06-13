#pragma once
#include <SFML/Graphics.hpp>
#include "Singleton.h"

class BaseScreen {
public:
    virtual ~BaseScreen() = default;
    virtual Screens_m handleEvents(sf::RenderWindow& window) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
};
