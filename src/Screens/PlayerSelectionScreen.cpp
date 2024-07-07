#include "PlayerSelectionScreen.h"
#include "LoadingManager.h"
#include <iostream>

// Constructor to initialize the player selection screen
PlayerSelectionScreen::PlayerSelectionScreen() : m_story(true) {
    try {
        setStory();
        if (!m_font.loadFromFile("arial.ttf")) {
            throw GameException("Failed to load font");
        }

        m_screen.setTexture(*(LoadingManager::instance().getScreen(PLAY_GAME_m)));

        std::vector<sf::Vector2f> positions = { sf::Vector2f(70, 165), sf::Vector2f(555, 165) ,sf::Vector2f(570, 518) }; // Positions for texts and rectangles

        std::string menuItems[] = { "One Player", "Two Players" ,"Go Back" };
        for (int i = 0; i < 3; ++i) {
            // Create a black rectangle below the text
            sf::RectangleShape rectangle(sf::Vector2f(200, 300)); // Set size of rectangle
            if (i == 2) rectangle.setSize(sf::Vector2f(200, 50));
            rectangle.setPosition(positions[i]); // Set positions
            rectangle.setOutlineThickness(8);
            rectangle.setFillColor(sf::Color::Black); // Color
            rectangle.setOutlineColor(sf::Color::Red); // Outline color for better visibility
            m_Rectangles.push_back(rectangle);

            sf::Text text(menuItems[i], m_font, 35);
            sf::FloatRect textBounds = text.getLocalBounds();
            // Set position slightly above the rectangle
            text.setPosition(positions[i].x + 30, positions[i].y + 120);
            if (i == 2) text.setPosition(positions[i].x + 30, positions[i].y);

            text.setFillColor(sf::Color::Red);
            m_Texts.push_back(text);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error initializing PlayerSelectionScreen: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error initializing PlayerSelectionScreen" << std::endl;
        throw;
    }
}

// Handle events for the player selection screen
Screens_m PlayerSelectionScreen::handleEvents(sf::RenderWindow& window) {
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
                            case 0:
                                return C1_m;
                            case 1:
                                return C2_m;
                            case 2:
                                return MENU_m;
                            default:
                                break;
                            }
                        }
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
    return PLAY_GAME_m; // Stay on the player selection screen
}

// Render the player selection screen
void PlayerSelectionScreen::render(sf::RenderWindow& window) {
    try {
        if (m_story) {
            gameStory(window);
            m_story = false;
        }

        window.draw(m_screen);
        for (size_t i = 0; i < m_Texts.size(); ++i) {
            window.draw(m_Rectangles[i]);
            window.draw(m_Texts[i]);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error rendering PlayerSelectionScreen: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error rendering PlayerSelectionScreen" << std::endl;
        throw;
    }
}

// Display the game story
void PlayerSelectionScreen::gameStory(sf::RenderWindow& window) {
    try {
        int i = 0;
        float transitionDuration = 0.5f; // Transition duration in seconds
        sf::Clock transitionClock;

        while (window.isOpen() && i != STORY_SCREENS) {
            window.clear();
            if (auto event = sf::Event{}; window.pollEvent(event)) {
                if (event.type == sf::Event::MouseButtonReleased) {
                    // play click
                    i++; // Move to the next screen after transition
                    transitionClock.restart();
                }
            }
            float interpolation = transitionClock.getElapsedTime().asSeconds() / transitionDuration;
            // Draw the current story screen
            drawStory(window, i, interpolation, i % 2);
            window.display();
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error displaying game story: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error displaying game story" << std::endl;
        throw;
    }
}

// Draw the story screen
void PlayerSelectionScreen::drawStory(sf::RenderWindow& window, unsigned int i, float interpolation, int animationIndex) {
    try {
        if (interpolation >= 1.0f) {
            interpolation = 1.0f;
        }

        sf::Uint8 alpha = static_cast<sf::Uint8>(255 * interpolation);
        float rotation = 360.0f * interpolation;

        switch (animationIndex) {
        case 0:
            m_storySprite[i].setColor(sf::Color(255, 255, 255, alpha));
            break;
        case 1:
            m_storySprite[i].setRotation(rotation);
            break;
        default:
            m_storySprite[i].setColor(sf::Color(255, 255, 255, alpha));
            break;
        }
        if (i < STORY_SCREENS) window.draw(m_storySprite[i]);
    }
    catch (const std::exception& e) {
        std::cerr << "Error drawing story screen: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error drawing story screen" << std::endl;
        throw;
    }
}

// Set up the story screens
void PlayerSelectionScreen::setStory() {
    try {
        m_storyTexture[0].loadFromFile("start.jpg");
        m_storySprite[0].setTexture(m_storyTexture[0]);
        for (size_t i = 1; i < STORY_SCREENS; i++) {
            m_storyTexture[i].loadFromFile(std::to_string(i) + ".jpg");
            m_storySprite[i].setTexture(m_storyTexture[i]);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error setting up story screens: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error setting up story screens" << std::endl;
        throw;
    }
}
