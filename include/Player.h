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
    sf::FloatRect getGlobalBounds() const;
    bool hasFallen() const;
    int getLives();
    void decrementLife();
    void resetCollisionFlag();
    bool isColliding() const;
private:
    bool isOnPlatform(const sf::FloatRect& platformBounds);
    void handleHorizontalMovement();
    int lives;
    bool currentlyColliding;
    sf::RectangleShape playerShape;
    float velocity;
    float gravity;
    float jumpStrength;
    float moveSpeed;
};
