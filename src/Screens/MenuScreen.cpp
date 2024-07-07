#include "MenuScreen.h"
#include "LoadingManager.h"
#include <iostream>
#include <cmath>

// Constructor to initialize the menu screen
MenuScreen::MenuScreen() :
    m_titleRect(200, 50, 400, 75),
    m_playButton(300, 200, 200, 50),
    m_helpButton(300, 275, 200, 50),
    m_settingsButton(300, 350, 200, 50),
    m_topScoresButton(300, 425, 200, 50),
    m_exitButton(300, 500, 200, 50),
    m_isWaving(false)
{
    try {
        m_screen.setTexture(*(LoadingManager::instance().getScreen(MENU_m)));

        if (!m_font.loadFromFile("arial.ttf")) {
            throw GameException("Failed to load font");
        }

        sf::Text titleText;
        titleText.setFont(m_font);
        titleText.setString("        Fell Fall");
        titleText.setCharacterSize(36);
        titleText.setFillColor(sf::Color::Black);
        titleText.setPosition(static_cast<float>(m_titleRect.left + 50.0), static_cast<float>(m_titleRect.top + 15.0));

        sf::RectangleShape titleRect;
        titleRect.setSize(sf::Vector2f(static_cast<float>(m_titleRect.width), static_cast<float>(m_titleRect.height)));
        titleRect.setPosition(static_cast<float>(m_titleRect.left), static_cast<float>(m_titleRect.top));
        titleRect.setFillColor(sf::Color(180, 50, 50, 250));

        m_Texts.push_back(titleText);
        m_Rectangles.push_back(titleRect);

        std::vector<std::pair<sf::IntRect*, std::string>> buttons = {
            {&m_playButton, "          Play"},
            {&m_helpButton, "          Help"},
            {&m_settingsButton, "         Setting"},
            {&m_topScoresButton, "       Top Score"},
            {&m_exitButton, "          Exit"}
        };

        for (auto& button : buttons)
        {
            sf::Text text;
            text.setFont(m_font);
            text.setString(button.second);
            text.setCharacterSize(24);
            text.setFillColor(sf::Color::White);
            text.setPosition(static_cast<float>(button.first->left) + 20.0f, static_cast<float>(button.first->top) + 10.0f);

            sf::RectangleShape rect;
            rect.setSize(sf::Vector2f(static_cast<float>(button.first->width), static_cast<float>(button.first->height)));
            rect.setPosition(static_cast<float>(button.first->left), static_cast<float>(button.first->top));
            rect.setFillColor(sf::Color(100, 100, 100, 200));

            m_Texts.push_back(text);
            m_Rectangles.push_back(rect);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error initializing MenuScreen: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error initializing MenuScreen" << std::endl;
        throw;
    }
}

// Handle events for the menu screen
Screens_m MenuScreen::handleEvents(sf::RenderWindow& window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        try {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                return MENU_m;
            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);

                    Menu_c button = getMenuButton(mousePos);

                    switch (button)
                    {
                    case PLAY_GAME_c:
                        Singleton::instance().getSoundManager().playSound("click");
                        return PLAY_GAME_m;
                    case HELP_c:
                        Singleton::instance().getSoundManager().playSound("click");
                        return HELP_m;
                    case SETTINGS_c:
                        Singleton::instance().getSoundManager().playSound("click");
                        return SETTINGS_m;
                    case HIGH_SCOORE_c:
                        Singleton::instance().getSoundManager().playSound("click");
                        return HIGH_SCOORE_m;
                    case EXIT_c:
                        Singleton::instance().getSoundManager().playSound("click");
                        window.close();
                        return MENU_m;
                    default:
                        break;
                    }
                }
                break;
            case sf::Event::MouseMoved:
                updateWavingText(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
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
    return MENU_m;
}

// Update the text animation based on mouse position
void MenuScreen::updateWavingText(sf::Vector2i mousePos)
{
    try {
        static const float waveAmplitude = 5.0f;
        static const float waveFrequency = 10.0f;

        for (size_t i = 1; i < m_Texts.size(); ++i)
        {
            if (m_Rectangles[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
            {
                float time = m_waveClock.getElapsedTime().asSeconds();
                float waveOffset = waveAmplitude * std::sin(time * waveFrequency);
                m_Texts[i].setPosition(static_cast<float>(m_Rectangles[i].getPosition().x) + 20.0f, static_cast<float>(m_Rectangles[i].getPosition().y) + 10.0f + waveOffset);
            }
            else {
                m_Texts[i].setPosition(static_cast<float>(m_Rectangles[i].getPosition().x) + 20.0f, static_cast<float>(m_Rectangles[i].getPosition().y) + 10.0f);
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error updating waving text: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error updating waving text" << std::endl;
        throw;
    }
}

// Render the menu screen
void MenuScreen::render(sf::RenderWindow& window)
{
    try {
        window.draw(m_screen);
        for (size_t i = 0; i < m_Rectangles.size(); ++i)
        {
            window.draw(m_Rectangles[i]);
            window.draw(m_Texts[i]);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error rendering MenuScreen: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error rendering MenuScreen" << std::endl;
        throw;
    }
}

// Get the menu button based on the mouse position
Menu_c MenuScreen::getMenuButton(sf::Vector2i mousePos)
{
    if (m_playButton.contains(mousePos)) {
        return PLAY_GAME_c;
    }
    else if (m_helpButton.contains(mousePos)) {
        return HELP_c;
    }
    else if (m_settingsButton.contains(mousePos)) {
        return SETTINGS_c;
    }
    else if (m_topScoresButton.contains(mousePos)) {
        return HIGH_SCOORE_c;
    }
    else if (m_exitButton.contains(mousePos)) {
        return EXIT_c;
    }
    return Menu_c();
}
