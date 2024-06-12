
#include "Screens.h"

#include "SoundManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> // Include the SFML Audio header
#include <iostream>


int main()

{


    SoundManager soundManager;

    sf::Texture texture;

    // Load an image file into the texture
    if (!texture.loadFromFile("menu.jpg")) // Change "menu.jpg" to the path of your image file
    {
        std::cerr << "Failed to load image" << std::endl;
        return 1;
    }
    soundManager.playMusic();

    // Get the size of the loaded image
    sf::Vector2u imageSize = texture.getSize();

    // Create a window with the size of the loaded image
    sf::RenderWindow window(sf::VideoMode(imageSize.x, imageSize.y), "SFML Image Loading Example");

    // Create a sprite and set its texture
    sf::Sprite sprite(texture);

    // Scale the background sprite to cover the entire window
    float scaleX = imageSize.x / sprite.getLocalBounds().width;
    float scaleY = imageSize.y / sprite.getLocalBounds().height;
    sprite.setScale(scaleX, scaleY);

    // Define the rectangles for menu options
    sf::IntRect playButton(410, 381, 655 - 410, 445 - 381);
    sf::IntRect helpButton(412, 470, 657 - 412, 541 - 470);
    sf::IntRect settingsButton(410, 559, 659 - 410, 630 - 559);
    sf::IntRect topScoresButton(412, 650, 659 - 412, 718 - 650);
    sf::IntRect exitButton(410, 741, 653 - 410, 807 - 741);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            //soundManager.playMusic();

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            // Check for mouse button pressed within the rectangles
            if (event.type == sf::Event::MouseButtonPressed)
            {
                // Play a sound effect
                soundManager.playSound("click");


                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (playButton.contains(mousePos))
                {
                    std::cout << "Play" << std::endl;
                    // Perform Play action
                }
                else if (helpButton.contains(mousePos))
                {
                    std::cout << "Help" << std::endl;
                    // Perform Help action
                }
                else if (settingsButton.contains(mousePos))
                {
                    std::cout << "Setting" << std::endl;
                    // Perform Setting action
                }
                else if (topScoresButton.contains(mousePos))
                {
                    std::cout << "Top 5" << std::endl;
                    // Perform Top 5 Scores action
                }
                else if (exitButton.contains(mousePos))
                {
                    std::cout << "Exit" << std::endl;
                    window.close();
                    return 0; // Exit the program or close the window
                }
            }
        }
        window.clear();

        window.draw(sprite);

        window.display();
    }


    return 0;
}