#include <SFML/Graphics.hpp>

class Player 
{
public:
    Player(float startX, float startY);

    void draw(sf::RenderWindow& window);
    void update();
    void jump();
    sf::Vector2f getPosition() const;


private:
    sf::RectangleShape playerShape;
    float velocity; // Speed
    float gravity;
    float jumpStrength;
    float moveSpeed; // Speed for left and right movement
};