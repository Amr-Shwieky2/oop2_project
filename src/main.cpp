#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Player.h"
#include "Platform.h"
#include "MovingPlatform.h"
#include "BreakablePlatform.h"

// Score variable
int score = 0;

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
    sf::RenderWindow window(sf::VideoMode(800, 600), "fell fall");
    window.setFramerateLimit(60);

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Couldn't load the font!" << std::endl;
        return -1;
    }

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

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();

        player.update(platforms, deltaTime);

        if (player.hasFallen()) {
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

        window.clear(sf::Color(100, 100, 255));

        player.draw(window);

        for (auto platform : platforms) {
            platform->draw(window);
        }

        sf::Text text;
        text.setFont(font);
        text.setString(std::to_string(score));
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::White);
        text.setStyle(sf::Text::Bold);
        text.setPosition(window.getSize().x / 2.0f, player.getPosition().y - 150);
        window.draw(text);

        window.display();
    }

    for (auto platform : platforms) {
        delete platform;
    }

    return 0;
}
