#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Player.h"
#include "Platform.h"
#include "MovingPlatform.h"
#include "BreakablePlatform.h"
#include "Bat.h"
#include "BlackHole.h"
#include "Sidebar.h"

// Score variable
int score = 0;
bool m_isGamePaused = false;
const int MEDIUM_HEIGHT = 30;  // Height at which the bat starts appearing
bool batActive = false;//whether the bat should be active or not
const float BAT_SPAWN_INTERVAL = 5.0f; // Time in seconds between bat appearances
float batTimer = 0; // Timer to manage bat spawn intervals
const int HARD_HEIGHT = 100; // Hard height after which the black hole starts appearing
BlackHole blackHole(-100, -100); // Initialize off-screen
float blackHoleTimer = 0;
const float BLACK_HOLE_SPAWN_INTERVAL = 10.0f; // Time in seconds between black hole appearances

void addNewPlatform(std::vector<Platform*>& platforms, float windowWidth, float gap) {
    float x = static_cast<float>(std::rand() % static_cast<int>(windowWidth - 60));
    float y = platforms.back()->getBounds().top - gap;
    Platform::Type type = static_cast<Platform::Type>(std::rand() % 3);

    switch (type)
    {
    case Platform::Type::NORMAL:
        platforms.push_back(new Platform(x, y));
        break;
    case Platform::Type::MOVING:
        platforms.push_back(new MovingPlatform(x, y));
        break;
    case Platform::Type::BREAKABLE:
        platforms.push_back(new BreakablePlatform(x, y));
        break;
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 650), "fell fall");

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Couldn't load the font!" << std::endl;
        return -1;
    }
    Sidebar sidebar(800, 50, font);
    window.setFramerateLimit(65);

    const int platformCount = 6;
    const float gap = static_cast<float>(window.getSize().y / 2) / platformCount;
    std::vector<Platform*> platforms;

    for (int i = 0; i < platformCount; ++i) {
        float x = static_cast<float>(std::rand() % (window.getSize().x - 60));
        float y = window.getSize().y - i * gap;
        platforms.push_back(new Platform(x, y));
    }

    float playerStartX = platforms[1]->getBounds().left + platforms[1]->getBounds().width / 2 - 25;
    float playerStartY = platforms[1]->getBounds().top - 50;
    Player player(playerStartX, playerStartY);

    Bat bat(-100, -100); //The bat is initialized 
    sf::Clock clock; // Clock to manage bat spawn timing

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Transform the mouse position to the view currently set on the window
                    sf::Vector2f worldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    sf::Vector2i transformedMousePos = static_cast<sf::Vector2i>(worldPos);
                    if (sidebar.isPaused(transformedMousePos)) {
                        m_isGamePaused = !m_isGamePaused;  // Toggle pause state
                        std::cout << (m_isGamePaused ? "Game Paused" : "Game Resumed") << std::endl;
                    }
                }
            }
        }

        //-----------------------------------------------levels-------------------------------
        float displayedHeight = playerStartY - player.getPosition().y;  // Height increases as the player goes up

        float deltaTime = clock.restart().asSeconds();
        // medium level
        if (player.getPosition().y < MEDIUM_HEIGHT)
        {
            batActive = true;
        }
        if (batActive)
        {
            batTimer += deltaTime;
            if (batTimer >= BAT_SPAWN_INTERVAL + 7.0f)
            {
                batTimer = 0; // Reset timer
                bat.resetPosition(window.getSize().x, player.getPosition().y - 300); // New bat position
            }
            bat.update(deltaTime); // Update bat position
            if (bat.getGlobalBounds().intersects(player.getGlobalBounds())) {
                player.decrementLife(); // Decrement lives only if not currently colliding
            }
            else if (player.isColliding()) {
                player.resetCollisionFlag(); // Reset flag if they are not colliding anymore
            }
        }
        //hard level
        if (player.getPosition().y < HARD_HEIGHT)
        {
            blackHoleTimer += deltaTime;
            if (blackHoleTimer >= BLACK_HOLE_SPAWN_INTERVAL)
            {
                blackHoleTimer = 0; // Reset timer
                blackHole.resetPosition(std::rand() % window.getSize().x, player.getPosition().y - 350); // New black hole position
            }
        }
        if (blackHole.getGlobalBounds().intersects(player.getGlobalBounds())) {
            window.close(); // Close the window to end the game, as the black hole ends the game on collision
        }
        //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        player.update(platforms, deltaTime);

        if (player.hasFallen() || player.getLives() == 0)
        {
            window.close();
        }

        sf::View view = window.getView();
        view.setCenter(view.getCenter().x, player.getPosition().y);
        window.setView(view);

        if (player.getPosition().y < platforms.back()->getBounds().top + 200) {
            addNewPlatform(platforms, window.getSize().x, gap);
        }

        if (!platforms.empty() && platforms[0]->getBounds().top > player.getPosition().y + 400) {
            delete platforms[0];
            platforms.erase(platforms.begin());
            score++;
        }

        sidebar.update(score, static_cast<int>(displayedHeight), player.getLives());

        window.clear(sf::Color(100, 100, 255));

        player.draw(window);
        bat.draw(window);
        blackHole.draw(window);
        for (auto platform : platforms) {
            platform->draw(window);
        }

        // Reset the view to the default view to draw the sidebar fixed at the top
        window.setView(window.getDefaultView());
        sidebar.draw(window);

        window.display();
    }

    for (auto platform : platforms) {
        delete platform;
    }

    return 0;
}
