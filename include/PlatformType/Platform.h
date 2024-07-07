#pragma once
#include <SFML/Graphics.hpp>
#include <string>

// Base class representing a platform in the game
class Platform {
public:
    enum class Type { NORMAL, MOVING, BREAKABLE, MOVING_BREAKABLE };

    Platform(float x, float y, Type type = Type::NORMAL); // Constructor
    virtual ~Platform() = default;

    virtual void update(float deltaTime); // Update platform state
    void draw(sf::RenderWindow& window); // Draw the platform
    sf::FloatRect getBounds() const; // Get the bounds of the platform
    bool isBreakable() const; // Check if the platform is breakable
    sf::Vector2f getPosition() const; // Get the position of the platform
    Type getType() const; // Get the type of the platform

    // Methods to save and restore state
    virtual std::string getTypeAsString() const; // Get the type of the platform as a string
    void restoreState(float x, float y, bool broken); // Restore the state of the platform

protected:
    sf::RectangleShape m_platformShape; // Shape of the platform
    Type m_type; // Type of the platform
    bool m_broken; // Flag indicating if the platform is broken
};
