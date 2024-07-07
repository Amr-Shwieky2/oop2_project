#include "Sidebar.h"
#include <iostream>
#include <algorithm>

// Constructor implementation
Sidebar::Sidebar(float width, float height)
    : m_sidebarWidth(width), m_sidebarHeight(height)
{
    try {
        // Load the font
        if (!m_font.loadFromFile("arial.ttf")) {
            throw std::runtime_error("Couldn't load the font!");
        }

        // Load the life texture
        if (!m_lifeTexture.loadFromFile("heart.png")) {
            throw std::runtime_error("Couldn't load the heart texture!");
        }

        // Set up the sidebar background
        m_background.setSize(sf::Vector2f(width, height));
        m_background.setFillColor(sf::Color(178, 34, 34)); // Dark fiery red

        // Set up the score text
        m_scoreText.setFont(m_font);
        m_scoreText.setCharacterSize(24);
        m_scoreText.setFillColor(sf::Color::Black);

        // Set up the pause button
        m_pauseButton.setSize(sf::Vector2f(70, 30));
        m_pauseButton.setFillColor(sf::Color::Transparent);
        m_pauseButton.setOutlineThickness(5);
        m_pauseButton.setOutlineColor(sf::Color::Black); // Outline color for better visibility

        // Set up the pause text
        m_pauseText.setFont(m_font);
        m_pauseText.setString("PAUSE");
        m_pauseText.setCharacterSize(24);
        m_pauseText.setFillColor(sf::Color::Black);

        // Load and sort high scores
        m_highScore = LoadingManager::instance().loadHighScore();
        std::sort(m_highScore.begin(), m_highScore.end(), [](const high_score& a, const high_score& b) {
            return a._score < b._score;
            });

        for (const auto& score : m_highScore) {
            std::cout << score._score << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error initializing Sidebar: " << e.what() << std::endl;
        std::exit(-1);
    }
    catch (...) {
        std::cerr << "Unknown error initializing Sidebar" << std::endl;
        std::exit(-1);
    }
}

// Find the next higher score to beat
int Sidebar::findNextHigherScore(int currentScore) {
    for (const auto& score : m_highScore) {
        if (currentScore < score._score) {
            return score._score;
        }
    }
    return currentScore; // If no higher score is found, return the current score
}

// Update the sidebar with the current score and lives
void Sidebar::update(int score, int lives) {
    try {
        int nextScore = findNextHigherScore(score);

        m_scoreText.setString("Score: " + std::to_string(score) +
            " Next Score: " + std::to_string(nextScore));

        m_livesSprites.clear();
        for (int i = 0; i < lives; ++i) {
            sf::Sprite lifeSprite;
            lifeSprite.setTexture(m_lifeTexture);
            lifeSprite.setScale(0.1f, 0.1f); // Scale down the heart image to 10% of its original size
            lifeSprite.setPosition(static_cast<float>(300 + i * 50), 0.f);
            m_livesSprites.push_back(lifeSprite);
        }

        m_background.setPosition(0, 0);
        m_scoreText.setPosition(10, 10);
        m_pauseButton.setPosition(700, 10);
        m_pauseText.setPosition(705, 12);
    }
    catch (const std::exception& e) {
        std::cerr << "Error updating Sidebar: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Unknown error updating Sidebar" << std::endl;
    }
}

// Draw the sidebar on the window
void Sidebar::draw(sf::RenderWindow& window) {
    try {
        window.draw(m_background);
        window.draw(m_scoreText);
        window.draw(m_pauseButton);
        window.draw(m_pauseText);
        for (const auto& sprite : m_livesSprites) {
            window.draw(sprite);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error drawing Sidebar: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Unknown error drawing Sidebar" << std::endl;
    }
}

// Check if the pause button was clicked
bool Sidebar::isPaused(sf::Vector2i mousePos) {
    try {
        return m_pauseButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
    }
    catch (const std::exception& e) {
        std::cerr << "Error checking if paused: " << e.what() << std::endl;
        return false;
    }
    catch (...) {
        std::cerr << "Unknown error checking if paused" << std::endl;
        return false;
    }
}
