#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Platform.h"
#include <vector>

class Player
{
public:
    Player();
    void setPosition(float startX, float startY);
    void draw(sf::RenderWindow& window);
    void update(std::vector<Platform*>& platforms, float deltaTime);
    void jump();
    sf::Vector2f getPosition() const;
    sf::FloatRect getGlobalBounds() const;
    bool hasFallen() const;
    int getLives() const;
    void decrementLife();
    void resetCollisionFlag();
    bool isColliding() const;

private:
    int m_lives;
    bool m_currentlyColliding;
    sf::RectangleShape m_playerShape;
    float m_velocity;
    float m_gravity;
    float m_jumpStrength;
    float m_moveSpeed;
};

#endif
