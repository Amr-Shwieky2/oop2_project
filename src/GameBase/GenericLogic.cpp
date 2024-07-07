#include "GenericLogic.h"
#include <iostream>

// Constructor to initialize the generic logic
GenericLogic::GenericLogic() : m_scoreBackground(sf::Vector2f(300.0f, 100.0f)) {
    try {
        if (!m_font.loadFromFile("arial.ttf")) {
            throw GameException("Couldn't load the font!");
        }
        m_scoreBackground.setFillColor(sf::Color::Black);
        m_scoreText.setFont(m_font);
        m_scoreText.setCharacterSize(24);
        m_scoreText.setFillColor(sf::Color::White);
    }
    catch (const std::exception& e) {
        std::cerr << "Error initializing GenericLogic: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error initializing GenericLogic" << std::endl;
        throw;
    }
}

// Initialize the game logic
void GenericLogic::initialize(sf::RenderWindow& window, Player& player, Map& map) {
    try {
        window.setFramerateLimit(60);
        map.initialize(window);
        player.resetPosition(map.getPlayerStartX(), map.getPlayerStartY());
    }
    catch (const std::exception& e) {
        std::cerr << "Error initializing game logic: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error initializing game logic" << std::endl;
        throw;
    }
}

// Update the game logic
void GenericLogic::update(float deltaTime, sf::RenderWindow& window, Player& player, Map& map, Sidebar& bar, bool& end) {
    try {
        map.collision(player);
        map.update(deltaTime, window, player);

        CenterView(window, player);
        isFail(player, end);
        bar.update(map.getScore(), player.getLives());
    }
    catch (const std::exception& e) {
        std::cerr << "Error updating game logic: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error updating game logic" << std::endl;
        throw;
    }
}

// Center the view
void GenericLogic::CenterView(sf::RenderWindow& window, Player& player) {
    sf::View view = window.getView();
    view.setCenter(view.getCenter().x, player.getPosition().y);
    window.setView(view);
}

// Render the game
void GenericLogic::render(sf::RenderWindow& window, Player& player, Map& map, Sidebar& bar, sf::Sprite& screen) {
    try {
        window.clear();

        sf::View view = window.getView();
        float viewTop = view.getCenter().y - view.getSize().y / 2;

        for (int i = 0; i < 3; ++i) {
            screen.setPosition(0, viewTop + i * screen.getTexture()->getSize().y);
            window.draw(screen);
        }

        player.draw(window);
        map.render(window);

        window.setView(window.getDefaultView());
        bar.draw(window);

        window.display();
    }
    catch (const std::exception& e) {
        std::cerr << "Error rendering game: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error rendering game" << std::endl;
        throw;
    }
}

// Save the game state
void GenericLogic::saveState(sf::Vector2f& savedPlayerPosition, float& savedPlayerVelocity, std::vector<Map::PlatformState>& savedPlatformStates, std::vector<Map::ObjectState>& savedObjectStates, Player& player, Map& map) {
    try {
        savedPlayerPosition = player.getPosition();
        savedPlayerVelocity = player.getVelocity();
        savedPlatformStates = map.getPlatformStates();
        savedObjectStates = map.getObjectStates();
    }
    catch (const std::exception& e) {
        std::cerr << "Error saving state: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error saving state" << std::endl;
        throw;
    }
}

// Restore the game state
void GenericLogic::restoreState(sf::Vector2f& savedPlayerPosition, float& savedPlayerVelocity, std::vector<Map::PlatformState>& savedPlatformStates, std::vector<Map::ObjectState>& savedObjectStates, Player& player, Map& map) {
    try {
        player.resetPosition(savedPlayerPosition.x, savedPlayerPosition.y);
        player.setVelocity(savedPlayerVelocity);
        map.setPlatformStates(savedPlatformStates);
        map.setObjectStates(savedObjectStates);
    }
    catch (const std::exception& e) {
        std::cerr << "Error restoring state: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error restoring state" << std::endl;
        throw;
    }
}

// Check if the player has failed
void GenericLogic::isFail(const Player& player, bool& end) {
    if (player.hasFallen() || player.getLives() <= 0) {
        end = true;
    }
}

// Show the end badge
void GenericLogic::showEndBadge(sf::RenderWindow& window, const std::string& message, const bool& end) {
    try {
        if (end) {
            m_scoreBackground.setPosition(window.getView().getCenter().x - 150, window.getView().getCenter().y - 50);

            m_scoreText.setString(message);
            m_scoreText.setPosition(window.getView().getCenter().x - 140, window.getView().getCenter().y - 40);

            window.draw(m_scoreBackground);
            window.draw(m_scoreText);
            window.display();

            sf::sleep(sf::seconds(3.0));
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error showing end badge: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error showing end badge" << std::endl;
        throw;
    }
}
