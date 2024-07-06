#include "Platform.h"

Platform::Platform(float x, float y, Type type)
    : m_type(type), m_broken(false)
{
    m_platformShape.setSize(sf::Vector2f(60, 15));
    m_platformShape.setFillColor(sf::Color(101, 67, 33));
    m_platformShape.setPosition(x, y);
}

void Platform::update(float) {}

void Platform::draw(sf::RenderWindow& window)
{
    if (!m_broken)
        window.draw(m_platformShape);
}

sf::FloatRect Platform::getBounds() const
{
    return m_platformShape.getGlobalBounds();
}

bool Platform::isBreakable() const
{
    return m_type == Type::BREAKABLE;
}

sf::Vector2f Platform::getPosition() const
{
    return m_platformShape.getPosition();
}

Platform::Type Platform::getType() const
{
    return m_type;
}

std::string Platform::getTypeAsString() const
{
    switch (m_type)
    {
    case Type::NORMAL:
        return "NORMAL";
    case Type::MOVING:
        return "MOVING";
    case Type::BREAKABLE:
        return "BREAKABLE";
    case Type::MOVING_BREAKABLE:
        return "MOVING_BREAKABLE";
    default:
        return "UNKNOWN";
    }
}

void Platform::restoreState(float x, float y, bool broken)
{
    m_platformShape.setPosition(x, y);
    m_broken = broken;
}
