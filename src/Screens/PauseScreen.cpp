#include "PauseScreen.h"
#include "GameLogic.h"

// Constructor to initialize the pause screen
PauseScreen::PauseScreen() {
    try {
        m_screen.setTexture(*(LoadingManager::instance().getScreen(PAUSE_m)));

        if (!m_font.loadFromFile("arial.ttf")) {
            throw GameException("Failed to load font");
        }

        sf::Text titleText;
        titleText.setFont(m_font);
        titleText.setString("PAUSED");
        titleText.setCharacterSize(36);
        titleText.setFillColor(sf::Color::Black);
        titleText.setPosition(static_cast<float>(m_titleRect.left + 20.0), static_cast<float>(m_titleRect.top + 15.0));

        sf::RectangleShape titleRect;
        titleRect.setSize(sf::Vector2f(static_cast<float>(m_titleRect.width), static_cast<float>(m_titleRect.height)));
        titleRect.setPosition(static_cast<float>(m_titleRect.left), static_cast<float>(m_titleRect.top));
        titleRect.setFillColor(sf::Color::Black);

        m_PauseScreenTexts.push_back(titleText);
        m_Rectangles.push_back(titleRect);

        std::vector<std::pair<sf::IntRect*, std::string>> buttons = {
            {&m_continue, "CONTINUE"},
            {&m_settings, "MENU"}
        };

        for (size_t i = 0; i < buttons.size(); ++i) {
            sf::Text text;
            text.setFont(m_font);
            text.setString(buttons[i].second);
            text.setCharacterSize(24);
            text.setFillColor(sf::Color::White);
            text.setPosition(static_cast<float>(320), static_cast <float>(200 + 120 * i));

            sf::RectangleShape rect;
            rect.setSize(sf::Vector2f(200, 50));
            rect.setPosition(static_cast<float>(300), static_cast<float>(100 + 120 * i));
            rect.setFillColor(sf::Color(100, 100, 100, 200));

            m_PauseScreenTexts.push_back(text);
            m_Rectangles.push_back(rect);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error initializing PauseScreen: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error initializing PauseScreen" << std::endl;
        throw;
    }
}

// Handle events for the pause screen
Screens_m PauseScreen::handleEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        try {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);

                    for (size_t i = 0; i < m_Rectangles.size(); ++i) {
                        if (m_Rectangles[i].getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                            Singleton::instance().getSoundManager().playSound("click");
                            switch (i) {
                            case 1: // CONTINUE button
                                Singleton::instance().getCurrentGameLogic().resumeGame(); // Ensure this method gets the current GameLogic instance
                                return GAME_m;
                            case 2:
                                return MENU_m;
                            default:
                                break;
                            }
                        }
                    }
                }
                break;
            case sf::Event::MouseMoved:
                updateWavingText(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
                break;
            default:
                break;
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Error handling events in PauseScreen: " << e.what() << std::endl;
            throw;
        }
        catch (...) {
            std::cerr << "Unknown error handling events in PauseScreen" << std::endl;
            throw;
        }
    }
    return PAUSE_m;
}

// Update the waving text effect
void PauseScreen::updateWavingText(sf::Vector2i mousePos) {
    static const float waveAmplitude = 5.0f;
    static const float waveFrequency = 10.0f;

    try {
        for (size_t i = 1; i < m_PauseScreenTexts.size(); ++i) {
            if (m_Rectangles[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                float time = m_waveClock.getElapsedTime().asSeconds();
                float waveOffset = waveAmplitude * std::sin(time * waveFrequency);
                m_PauseScreenTexts[i].setPosition(static_cast<float>(m_Rectangles[i].getPosition().x) + 20.0f, static_cast<float>(m_Rectangles[i].getPosition().y) + 10.0f + waveOffset);
            }
            else {
                m_PauseScreenTexts[i].setPosition(static_cast<float>(m_Rectangles[i].getPosition().x) + 20.0f, static_cast<float>(m_Rectangles[i].getPosition().y) + 10.0f);
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error updating waving text in PauseScreen: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error updating waving text in PauseScreen" << std::endl;
        throw;
    }
}

// Render the pause screen
void PauseScreen::render(sf::RenderWindow& window) {
    try {
        window.draw(m_screen);
        for (size_t i = 0; i < m_Rectangles.size(); ++i) {
            window.draw(m_Rectangles[i]);
            window.draw(m_PauseScreenTexts[i]);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error rendering PauseScreen: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error rendering PauseScreen" << std::endl;
        throw;
    }
}
