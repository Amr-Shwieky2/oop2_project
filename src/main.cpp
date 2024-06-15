#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Player.h"
#include "Platform.h"

int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Doodle Game");

    // Seed random number generator
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Create a player object
    Player player(375, 500); // Starting position in the middle-bottom of the window

    // Create initial platforms
    const int platformCount = 6;
    const float gap = static_cast<float>(window.getSize().y) / platformCount;
    std::vector<Platform> platforms;

    for (int i = 0; i < platformCount; ++i) {
        float x = static_cast<float>(std::rand() % window.getSize().x);
        float y = window.getSize().y - i * gap;
        platforms.emplace_back(x, y);
    }

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // Check for spacebar press to trigger jump
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                player.jump();
            }
        }

        // Update the player (apply gravity and handle movement)
        player.update();

        // Adjust the view to keep the player centered
        sf::View view = window.getView();
        view.setCenter(view.getCenter().x, player.getPosition().y);
        window.setView(view);

        // Create more platforms as the player moves up the screen
        if (player.getPosition().y < platforms.back().getBounds().top + 200) {
            float x = static_cast<float>(std::rand() % window.getSize().x);
            float y = platforms.back().getBounds().top - gap;
            platforms.emplace_back(x, y);
        }

        // Clear screen
        window.clear(sf::Color(100, 100, 255)); // Set background color

        // Draw the player
        player.draw(window);

        // Draw the platforms
        for (auto& platform : platforms) {
            platform.draw(window);
        }

        // Update the window
        window.display();
    }

    return 0;
}


    //// Create a texture
    //sf::Texture texture;

    //// Load an image file into the texture
    //if (!texture.loadFromFile("setting.jpg")) // Change "menu.jpg" to the path of your image file
    //{
    //    std::cerr << "Failed to load image" << std::endl;
    //    return 1;
    //}

    //// Get the size of the loaded image
    //sf::Vector2u imageSize = texture.getSize();

    //// Create a window with the size of the loaded image
    //sf::RenderWindow window(sf::VideoMode(imageSize.x, imageSize.y), "SFML Image Loading Example");

    //// Create a sprite and set its texture
    //sf::Sprite sprite(texture);

    //// Main loop
    //while (window.isOpen())
    //{
    //    sf::Event event;
    //    while (window.pollEvent(event))
    //    {
    //        if (event.type == sf::Event::Closed)
    //            window.close();

    //        // Check if the event is a mouse button release
    //        if (event.type == sf::Event::MouseButtonReleased)
    //        {
    //            // Get the mouse position
    //            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    //           
    //            // Check if the mouse position falls within the specified ranges
    //                std::cout << "x = " << mousePos.x << "y = " << mousePos.y << std::endl;
    //            
    //        }
    //    }

    //    // Clear the window
    //    window.clear();

    //    // Draw the sprite
    //    window.draw(sprite);

    //    // Display the window
    //    window.display();
    //}
//
//    return 0;
//}
