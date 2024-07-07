#include "SinglePlayerSidebar.h"

SinglePlayerSidebar::SinglePlayerSidebar(float width, float height)
    : BaseSidebar(width, height)
{
}

void SinglePlayerSidebar::update(int score, int height, int lives)
{
    m_scoreText.setString("Score: " + std::to_string(score));
    m_heightText.setString("Height: " + std::to_string(std::max(0, height)));

    m_livesSprites.clear();
    for (int i = 0; i < lives; ++i)
    {
        sf::Sprite lifeSprite;
        lifeSprite.setTexture(m_lifeTexture);
        lifeSprite.setScale(0.1f, 0.1f);  // Scale down the heart image to 10% of its original size
        lifeSprite.setPosition(static_cast<float>(300 + i * 50), 0.f);
        m_livesSprites.push_back(lifeSprite);
    }

    m_background.setPosition(0, 0);
    m_scoreText.setPosition(10, 10);
    m_heightText.setPosition(100, 10);
    m_pauseButton.setPosition(700, 10);
    m_pauseText.setPosition(705, 12);
}