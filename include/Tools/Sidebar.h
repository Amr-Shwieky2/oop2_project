#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "LoadingManager.h"

// Class to manage the game's sidebar, which displays the score, lives, and pause button
class Sidebar {
public:
    Sidebar(float width, float height); // Constructor

    void update(int score, int lives); // Update the sidebar with the current score and lives
    void draw(sf::RenderWindow& window); // Draw the sidebar on the window
    bool isPaused(sf::Vector2i mousePos); // Check if the pause button was clicked

private:
    sf::RectangleShape m_background; // Sidebar background shape
    sf::Text m_scoreText; // Text to display the score
    sf::Text m_pauseText; // Text to display the pause button
    sf::RectangleShape m_pauseButton; // Pause button shape
    std::vector<sf::Sprite> m_livesSprites; // Sprites to display the lives
    std::vector<high_score> m_highScore; // List of high scores
    sf::Texture m_lifeTexture; // Texture for the life sprite
    sf::Font m_font; // Font for the text
    float m_sidebarWidth; // Width of the sidebar
    float m_sidebarHeight; // Height of the sidebar

    int findNextHigherScore(int currentScore); // Find the next higher score to beat
};
