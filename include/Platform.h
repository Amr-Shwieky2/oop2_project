#ifndef PLATFORM_H
#define PLATFORM_H

#include <SFML/Graphics.hpp>

class Platform {
public:
    Platform(float x, float y);

    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;

private:
    sf::RectangleShape platformShape;
};

#endif
