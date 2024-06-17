#include "HighScoreScreen.h"
#include <iostream>

HighScoreScreen::HighScoreScreen() :
    m_backButton(230, 800, 465 - 230, 835 - 800) {
    m_screen.setTexture(*(Singleton::instance().getScreen(HIGH_SCOORE_m)));

    // Load the high scores
    auto highScores = Singleton::instance().loadHighScore();

    // Load the font
    if (!m_font.loadFromFile("arial.ttf")) {
        throw GameException("Failed to load font");
    }

    // Prepare text objects for high scores
    float yPos = 349;
    for (const auto& score : highScores) {
        sf::Text nameText;
        nameText.setFont(m_font);
        nameText.setString(score._name);
        nameText.setCharacterSize(24);
        nameText.setFillColor(sf::Color::White);
        nameText.setPosition(200, yPos);

        sf::Text scoreText;
        scoreText.setFont(m_font);
        scoreText.setString(std::to_string(score._score));
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(450, yPos);

        m_highScoreTexts.push_back(nameText);
        m_highScoreTexts.push_back(scoreText);

        yPos += 70;  // Adjust this value as needed to space the scores vertically
    }
}

Screens_m HighScoreScreen::handleEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            window.close();
            return HIGH_SCOORE_m;  // or a specific screen type for closing
        case sf::Event::MouseButtonReleased:
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
                std::cout << "x: " << mousePos.x << " y: " << mousePos.y;

                if (m_backButton.contains(mousePos)) {
                    Singleton::instance().getSoundManager().playSound("click"); // Play click sound
                    return MENU_m;  // Return to menu screen
                }
            }
            break;
        }
    }
    return HIGH_SCOORE_m;
}

void HighScoreScreen::render(sf::RenderWindow& window) {
    window.draw(m_screen);

    // Draw high scores
    for (const auto& text : m_highScoreTexts) {
        window.draw(text);
    }
}
