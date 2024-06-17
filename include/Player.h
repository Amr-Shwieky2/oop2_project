#include <SFML/Graphics.hpp>
#include "Platform.h"
#include <vector>

class Player 
{
public:
    Player(float startX, float startY);

    void draw(sf::RenderWindow& window);
    void update(const std::vector<Platform>& platforms);
    void jump();
    sf::Vector2f getPosition() const;
    bool hasFallen() const;

private:
    sf::RectangleShape playerShape;
    float velocity; // Speed of moving up or down (affected by gravity and jumping)
    float gravity;
    float jumpStrength;
    float moveSpeed; // Speed for left and right movement
};