#include <SFML/Graphics.hpp>

class Player {
public:
    sf::RectangleShape shape;
    float speed;

    Player(sf::Vector2f position, sf::Color color) {
        shape.setSize(sf::Vector2f(50, 50));
        shape.setPosition(position);
        shape.setFillColor(color);
        speed = 200.0f;
    }

    void handleInput(sf::Keyboard::Key up, sf::Keyboard::Key down, sf::Keyboard::Key left, sf::Keyboard::Key right, float deltaTime) {
        if (sf::Keyboard::isKeyPressed(up))
            shape.move(0, -speed * deltaTime);
        if (sf::Keyboard::isKeyPressed(down))
            shape.move(0, speed * deltaTime);
        if (sf::Keyboard::isKeyPressed(left))
            shape.move(-speed * deltaTime, 0);
        if (sf::Keyboard::isKeyPressed(right))
            shape.move(speed * deltaTime, 0);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Two Player Split Screen");

    sf::View leftView(sf::FloatRect(0, 0, 400, 600));
    leftView.setViewport(sf::FloatRect(0, 0, 0.5f, 1.0f));

    sf::View rightView(sf::FloatRect(400, 0, 400, 600));
    rightView.setViewport(sf::FloatRect(0.5f, 0, 0.5f, 1.0f));

    Player player1(sf::Vector2f(100, 100), sf::Color::Green);
    Player player2(sf::Vector2f(500, 100), sf::Color::Blue);

    // Create a line to separate the views
    sf::RectangleShape line(sf::Vector2f(2, 600));
    line.setPosition(400, 0);
    line.setFillColor(sf::Color::Red);

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();

        // Update players
        player1.handleInput(sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D, deltaTime);
        player2.handleInput(sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right, deltaTime);

        window.clear();

        // Draw the left view
        window.setView(leftView);
        player1.draw(window);

        // Draw the right view
        window.setView(rightView);
        player2.draw(window);

        // Draw the separating line in the default view
        window.setView(window.getDefaultView());
        window.draw(line);

        window.display();
    }

    return 0;
}
