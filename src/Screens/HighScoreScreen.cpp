#include "HighScoreScreen.h"
#include "LoadingManager.h"
#include "GameException.h"
#include <iostream>

// Constructor to initialize the high score screen
HighScoreScreen::HighScoreScreen() :
    m_backButton(230, 800, 235, 35) { // Initialize back button rectangle
    try {
        m_screen.setTexture(*(LoadingManager::instance().getScreen(HIGH_SCOORE_m)));
        Singleton::instance().getSoundManager().playSound("top5");

        // Load the font
        if (!m_font.loadFromFile("arial.ttf")) {
            throw GameException("Failed to load font");
        }

        // Initialize the back button shape
        m_backButtonShape.setSize(sf::Vector2f(100, 50)); // Set size of the back button
        m_backButtonShape.setPosition(360, 495); // Set position of the back button
        m_backButtonShape.setFillColor(sf::Color::Black); // Set fill color of the back button
        m_backButtonShape.setOutlineColor(sf::Color::Red); // Set outline color of the back button
        m_backButtonShape.setOutlineThickness(2); // Set outline thickness of the back button

        // Initialize the back button text
        m_backText.setFont(m_font);
        m_backText.setString("BACK");
        m_backText.setCharacterSize(24);
        m_backText.setFillColor(sf::Color::White);
        m_backText.setPosition(380, 505);

        update(); // Update the high score texts

    }
    catch (const std::exception& e) {
        std::cerr << "Error initializing HighScoreScreen: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error initializing HighScoreScreen" << std::endl;
        throw;
    }
}

// Update the high score texts
void HighScoreScreen::update() {
    try {
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
    catch (const std::exception& e) {
        std::cerr << "Error updating high scores: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error updating high scores" << std::endl;
        throw;
    }
}

// Handle events for the high score screen
Screens_m HighScoreScreen::handleEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        try {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                return HIGH_SCOORE_m;
            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
                    if (m_backButtonShape.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        Singleton::instance().getSoundManager().playSound("click"); // Play click sound
                        return MENU_m; // Return to menu screen
                    }
                }
                break;
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Error handling events: " << e.what() << std::endl;
            throw;
        }
        catch (...) {
            std::cerr << "Unknown error handling events" << std::endl;
            throw;
        }
    }
    return HIGH_SCOORE_m;
}

// Render the high score screen
void HighScoreScreen::render(sf::RenderWindow& window) {
    try {
        update(); // Update the high score texts before rendering
        window.draw(m_screen);
        window.draw(m_backButtonShape);
        window.draw(m_backText);

        for (const auto& text : m_highScoreTexts) {
            window.draw(text);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error rendering HighScoreScreen: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error rendering HighScoreScreen" << std::endl;
        throw;
    }
}
