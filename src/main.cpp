#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    // Create a texture
    sf::Texture texture;

    // Load an image file into the texture
    if (!texture.loadFromFile("setting.jpg")) // Change "menu.jpg" to the path of your image file
    {
        std::cerr << "Failed to load image" << std::endl;
        return 1;
    }

    // Get the size of the loaded image
    sf::Vector2u imageSize = texture.getSize();

    // Create a window with the size of the loaded image
    sf::RenderWindow window(sf::VideoMode(imageSize.x, imageSize.y), "SFML Image Loading Example");

    // Create a sprite and set its texture
    sf::Sprite sprite(texture);

    // Main loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // Check if the event is a mouse button release
            if (event.type == sf::Event::MouseButtonReleased)
            {
                // Get the mouse position
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
               
                // Check if the mouse position falls within the specified ranges
                    std::cout << "x = " << mousePos.x << "y = " << mousePos.y << std::endl;
                
            }
        }

        // Clear the window
        window.clear();

        // Draw the sprite
        window.draw(sprite);

        // Display the window
        window.display();
    }

    return 0;
}
