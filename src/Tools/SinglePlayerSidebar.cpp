#include "SinglePlayerSidebar.h"
#include "SinglePlayerSidebar.h"
#include "LoadingManager.h"
#include <iostream>
#include <algorithm>

SinglePlayerSidebar::SinglePlayerSidebar(float width, float height)
    : BaseSidebar(width, height)
{
    try {
        // Load and sort high scores
        m_highScore = LoadingManager::instance().loadHighScore();
        std::sort(m_highScore.begin(), m_highScore.end(), [](const high_score& a, const high_score& b) {
            return a._score < b._score;
            });
    }
    catch (const std::exception& e) {
        std::cerr << "Error initializing SinglePlayerSidebar: " << e.what() << std::endl;
        std::exit(-1);
    }
    catch (...) {
        std::cerr << "Unknown error initializing SinglePlayerSidebar" << std::endl;
        std::exit(-1);
    }
}

// Find the next higher score to beat
int SinglePlayerSidebar::findNextHigherScore(int currentScore) {
    for (const auto& score : m_highScore) {
        if (currentScore < score._score) {
            return score._score;
        }
    }
    return currentScore; // If no higher score is found, return the current score
}

void SinglePlayerSidebar::update(int score, int lives) {
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
        std::cerr << "Error updating SinglePlayerSidebar: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Unknown error updating SinglePlayerSidebar" << std::endl;
    }
}

void SinglePlayerSidebar::draw(sf::RenderWindow& window)
{

    window.draw(m_background);
    window.draw(m_scoreText);
    window.draw(m_pauseButton);
    window.draw(m_pauseText);
    for (auto& sprite : m_livesSprites)
    {
        window.draw(sprite);
    }
}
