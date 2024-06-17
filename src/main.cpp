#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Player.h"
#include "Platform.h"

// Score variable
int score = 0;

int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "fell fall");

        // Seed random number generator
        std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Create initial platforms
    const int platformCount = 6;//Defines the number of platforms 
    const float gap = static_cast<float>(window.getSize().y/2) / platformCount;
    std::vector<Platform> platforms;

    for (int i = 0; i < platformCount; ++i)
    {
        float x = static_cast<float>(std::rand() % window.getSize().x);
        float y = window.getSize().y - i * gap;
        platforms.emplace_back(x, y);
    }

    // Create a player object and place it just above the second platform
    float playerStartX = platforms[1].getBounds().left + platforms[1].getBounds().width / 2 - 25;
    float playerStartY = platforms[1].getBounds().top - 50;
    Player player(playerStartX, playerStartY);

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Update the player (apply gravity and handle movement)
        player.update(platforms);

        // Check if the player has fallen off the screen
        if (player.hasFallen())
        {
            window.close(); // Close the window to end the game
        }

        // Adjust the view to keep the player centered
        sf::View view = window.getView();//defines what part of the game world is visible on the screen
        view.setCenter(view.getCenter().x, player.getPosition().y);// keeps the player vertically centered in the view
        window.setView(view);

        // Create more platforms as the player moves up the screen
        if (player.getPosition().y < platforms.back().getBounds().top + 200)
        {
            float x = static_cast<float>(std::rand() % window.getSize().x);// generates a random x-coordinate for the new platform
            float y = platforms.back().getBounds().top - gap; // calculates the y-coordinate for the new platform
            platforms.emplace_back(x, y);//adds the new platform to the platforms vector
        }

        // Remove platforms that are off the screen and increment score
        if (!platforms.empty() && platforms[0].getBounds().top > player.getPosition().y + 400) {
            platforms.erase(platforms.begin());
            score++;
        }

        // Clear screen
        window.clear(sf::Color(100, 100, 255)); // Set background color

        // Draw the player
        player.draw(window);

        // Draw the platforms
        for (auto& platform : platforms)
        {
            platform.draw(window);
        }

        // Display the score
        sf::Font font;
        if (!font.loadFromFile("arial.ttf"))
        {
            std::cout << "could't laod the font ";
        }
        sf::Text text;
        text.setFont(font);
        text.setString(std::to_string(score));
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::White);
        text.setStyle(sf::Text::Bold);
        text.setPosition(window.getSize().x / 2.0f, player.getPosition().y - 150);
        window.draw(text);

        // Update the window
        window.display();
    }

    return 0;
}