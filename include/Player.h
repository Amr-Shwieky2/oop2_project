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
    int getLives();
    void decrementLife();
    void resetCollisionFlag();
    bool isColliding() const;
private:
    
    int lives;
    bool currentlyColliding;
    sf::RectangleShape playerShape;
    float velocity;
    float gravity;
    float jumpStrength;
    float moveSpeed;
};

#endif
