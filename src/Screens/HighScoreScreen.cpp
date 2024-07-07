#include "HighScoreScreen.h"
#include <iostream>

HighScoreScreen::HighScoreScreen() :
    m_backButton(230, 800, 465 - 230, 835 - 800) {
    m_screen.setTexture(*(LoadingManager::instance().getScreen(HIGH_SCOORE_m)));
    Singleton::instance().getSoundManager().playSound("top5");

    // Load the font
    if (!m_font.loadFromFile("arial.ttf")) {
        throw GameException("Failed to load font");
    }


    m_backButtonShape.setSize(sf::Vector2f(100, 50));  // Size based on your existing IntRect
    m_backButtonShape.setPosition(360, 495);  // Position
    m_backButtonShape.setFillColor(sf::Color::Black);  // Color
    m_backButtonShape.setOutlineColor(sf::Color::Red);  // Outline color for better visibility
    m_backButtonShape.setOutlineThickness(2);  // Outline thickness

    m_backText.setFont(m_font);
    m_backText.setString("BACK");
    m_backText.setCharacterSize(24);
    m_backText.setFillColor(sf::Color::White);
    m_backText.setPosition(380, 505);
    update();
    
}

void HighScoreScreen::update()
{
    // Load the high scores
    auto highScores = LoadingManager::instance().loadHighScore();
    m_highScoreTexts.clear();
    float yPos = 210;
    for (const auto& score : highScores) {
        sf::Text nameText;
        nameText.setFont(m_font);
        nameText.setString(score._name);
        nameText.setCharacterSize(23);
        nameText.setFillColor(sf::Color::White);
        nameText.setPosition(320, yPos);

        sf::Text scoreText;
        scoreText.setFont(m_font);
        scoreText.setString(std::to_string(score._score));
        scoreText.setCharacterSize(23);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(440, yPos);

        m_highScoreTexts.push_back(nameText);
        m_highScoreTexts.push_back(scoreText);

        yPos += 40;
    }
}

Screens_m HighScoreScreen::handleEvents(sf::RenderWindow& window) {
    
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            window.close();
            return HIGH_SCOORE_m; 
        case sf::Event::MouseButtonReleased:
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
                std::cout << "x: " << mousePos.x << " y: " << mousePos.y;

                if (m_backButtonShape.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
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
    update();
    window.draw(m_screen);
    window.draw(m_backButtonShape);
    window.draw(m_backText);

    //if (m_highScoreTexts.empty()) {
    //    std::cout << "No high scores to display." << std::endl; // Debug output
    //}

    for (const auto& text : m_highScoreTexts) {
        window.draw(text);
    }
}

