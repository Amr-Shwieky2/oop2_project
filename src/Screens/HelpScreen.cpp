#include "HelpScreen.h"
#include "LoadingManager.h"
#include "GameException.h"
#include <iostream>

// Constructor to initialize the help screen
HelpScreen::HelpScreen() {
    try {
        if (!m_font.loadFromFile("arial.ttf")) {
            throw GameException("Failed to load font");
        }
        m_screen.setTexture(*(LoadingManager::instance().getScreen(HELP_m)));

        std::vector<sf::Vector2f> positions = {
            sf::Vector2f(353, 100), sf::Vector2f(665, 40), sf::Vector2f(157, 265),
            sf::Vector2f(7, 370), sf::Vector2f(523, 374), sf::Vector2f(652, 449),
            sf::Vector2f(4, 540), sf::Vector2f(695, 515)
        };

        std::string menuItems[] = {
            "FELL FALL", "THIS IS YOUR \n\n\n   HELL!",
            "YOUR WAY OUT IS JUMPING UP AND AVOIDING FALLING DOWN!",
            "you only have three precious lives",
            "DON'T lose!",
            "USE THE GIFTS",
            "WELL, CAN YOU STAY ALIVE?",
            "BACK"
        };

        for (int i = 0; i < 8; ++i) {
            sf::Text text(menuItems[i], m_font, 22);
            sf::FloatRect textBounds = text.getLocalBounds();
            text.setPosition(positions[i]);
            text.setFillColor(sf::Color::White);
            m_Texts.push_back(text);
        }

        m_backButton.setSize(sf::Vector2f(100, 50));
        m_backButton.setOutlineThickness(5);
        m_backButton.setOutlineColor(sf::Color::Red);
        m_backButton.setFillColor(sf::Color::Black);
        m_backButton.setPosition(680, 500);
    }
    catch (const std::exception& e) {
        std::cerr << "Error initializing HelpScreen: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error initializing HelpScreen" << std::endl;
        throw;
    }
}

// Handle events for the help screen
Screens_m HelpScreen::handleEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        try {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                return HELP_m; // or a specific screen type for closing
            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);

                    if (m_backButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
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
    return HELP_m;
}

// Render the help screen
void HelpScreen::render(sf::RenderWindow& window) {
    try {
        window.draw(m_screen);
        window.draw(m_backButton);
        for (size_t i = 0; i < m_Texts.size(); ++i) {
            window.draw(m_Texts[i]);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error rendering HelpScreen: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error rendering HelpScreen" << std::endl;
        throw;
    }
}
