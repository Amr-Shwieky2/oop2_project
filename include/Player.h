#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Platform.h"
#include <vector>

class Player
{
public:
    Player(float startX, float startY);

    void draw(sf::RenderWindow& window);
    void update(std::vector<Platform*>& platforms, float deltaTime);
    void jump();
    sf::Vector2f getPosition() const;
    bool hasFallen() const;

private:
    sf::RectangleShape playerShape;
    float velocity;
    float gravity;
    float jumpStrength;
    float moveSpeed;
};

#endif
