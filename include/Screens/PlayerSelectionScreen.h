#pragma once
#include "BaseScreen.h"
#include "Singleton.h"
#include <SFML/Graphics.hpp>
#include <vector>

// Class representing the player selection screen
class PlayerSelectionScreen : public BaseScreen {
public:
    PlayerSelectionScreen();
    Screens_m handleEvents(sf::RenderWindow& window) override; // Handle events for the player selection screen
    void render(sf::RenderWindow& window) override; // Render the player selection screen

private:
    void gameStory(sf::RenderWindow& window); // Display the game story
    void drawStory(sf::RenderWindow& window, unsigned int index, float interpolation, int animationIndex); // Draw the story screen
    void setStory(); // Set up the story screens

    bool m_story; // Flag for story display

    sf::Sprite m_screen; // Background sprite for the player selection screen

    // Define the rectangles for play mode options
    sf::IntRect onePlayerButton;
    sf::IntRect twoPlayersButton;
    sf::IntRect m_backButton;

    sf::Font m_font; // Font for the text
    std::vector<sf::Text> m_Texts; // Texts for the player selection options
    std::vector<sf::RectangleShape> m_Rectangles; // Rectangles for the player selection options

    sf::Texture m_storyTexture[STORY_SCREENS]; // Textures for the story screens
    sf::Sprite m_storySprite[STORY_SCREENS]; // Sprites for the story screens
};
