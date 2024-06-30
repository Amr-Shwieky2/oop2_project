#ifndef PLATFORM_H
#define PLATFORM_H

#include <SFML/Graphics.hpp>

class Platform
{
public:
    enum class Type { NORMAL, MOVING, BREAKABLE };

    Platform(float x, float y, Type type = Type::NORMAL);
    virtual ~Platform() = default;

    virtual void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    bool isBreakable() const;
    Type getType() const;
protected:
    sf::RectangleShape m_platformShape;
    Type m_type;
    bool m_broken;
};

#endif
