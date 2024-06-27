#include "HighScoreScreen.h"
#include <iostream>

HighScoreScreen::HighScoreScreen() : m_backButton(230, 800, 235, 35) {
    m_screen.setTexture(*(Singleton::instance().getScreen(HIGH_SCOORE_m)));

    if (!m_font.loadFromFile("arial.ttf")) {
        throw GameException("Failed to load font");
    }
    updateHighScores();
}

void HighScoreScreen::updateHighScores() {
    auto highScores = Singleton::instance().loadHighScore();
    m_highScoreTexts.clear();
    float yPos = 349;
    for (const auto& score : highScores) {
        sf::Text nameText;
        nameText.setFont(m_font);
        nameText.setString(score.name);
        nameText.setCharacterSize(24);
        nameText.setFillColor(sf::Color::White);
        nameText.setPosition(200, yPos);

        sf::Text scoreText;
        scoreText.setFont(m_font);
        scoreText.setString(std::to_string(score.score));
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(450, yPos);

        m_highScoreTexts.push_back(nameText);
        m_highScoreTexts.push_back(scoreText);

        yPos += 70;
    }
}

Screens_m HighScoreScreen::handleEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            return HIGH_SCOORE_m;
        }
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
            if (m_backButton.contains(mousePos)) {
                Singleton::instance().getSoundManager().playSound("click");
                return MENU_m;
            }
        }
    }
    return HIGH_SCOORE_m;
}

void HighScoreScreen::render(sf::RenderWindow& window) {
    updateHighScores();
    window.draw(m_screen);
    for (const auto& text : m_highScoreTexts) {
        window.draw(text);
    }
}
