#include "TwoPlayerSidebar.h"
#include <iostream>
TwoPlayerSidebar::TwoPlayerSidebar(float width, float height)
    : BaseSidebar(width, height)
{
    m_scoreText2.setFont(m_font);
    m_scoreText2.setCharacterSize(24);
    m_scoreText2.setFillColor(sf::Color::Black);
}

void TwoPlayerSidebar::update(int score1, int lives1, int score2, int lives2) {
    try {
        m_scoreText.setString("Score1: " + std::to_string(score1));
        m_scoreText2.setString("Score2: " + std::to_string(score2));

        m_livesSprites.clear();
        for (int i = 0; i < lives1; ++i) {
            sf::Sprite lifeSprite;
            lifeSprite.setTexture(m_lifeTexture);
            lifeSprite.setScale(0.1f, 0.1f); // Scale down the heart image to 10% of its original size
            lifeSprite.setPosition(static_cast<float>(120 + i * 50), 0.f);
            m_livesSprites.push_back(lifeSprite);
        }

        m_livesSprites2.clear();
        for (int i = 0; i < lives2; ++i) {
            sf::Sprite lifeSprite;
            lifeSprite.setTexture(m_lifeTexture);
            lifeSprite.setScale(0.1f, 0.1f); // Scale down the heart image to 10% of its original size
            lifeSprite.setPosition(static_cast<float>(620 + i * 50), 0.f);
            m_livesSprites2.push_back(lifeSprite);
        }

        m_background.setPosition(0, 0);
        m_scoreText.setPosition(10, 10);
        m_scoreText2.setPosition(510, 10);
        m_pauseButton.setPosition(380, 10);
        m_pauseText.setPosition(385, 12);
    }
    catch (const std::exception& e) {
        std::cerr << "Error updating SinglePlayerSidebar: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Unknown error updating SinglePlayerSidebar" << std::endl;
    }
    
}

void TwoPlayerSidebar::draw(sf::RenderWindow& window) {
    window.draw(m_background);
    window.draw(m_scoreText);
    window.draw(m_scoreText2);
    window.draw(m_pauseButton);
    window.draw(m_pauseText);
    for (const auto& sprite : m_livesSprites) {
        window.draw(sprite);
    }
    for (const auto& sprite : m_livesSprites2) {
        window.draw(sprite);
    }
}