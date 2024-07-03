#pragma once
#include <SFML/Graphics.hpp>

class Platform {
public:
    enum class Type { NORMAL, MOVING, BREAKABLE };

    Platform(float x, float y, Type type = Type::NORMAL);
    virtual ~Platform() = default;

    virtual void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    bool isBreakable() const;
    sf::Vector2f getPosition() const;
    Type getType() const;

    // Methods to save and restore state
    virtual std::string getTypeAsString() const;
    virtual void restoreState(float x, float y, bool broken);

protected:
    sf::RectangleShape m_platformShape;
    Type m_type;
    bool m_broken;
};
