#include "Sidebar.h"

Sidebar::Sidebar(float width, float height, const sf::Font& font)
    : font(font), sidebarWidth(width), sidebarHeight(height) 
{
    background.setSize(sf::Vector2f(width, height));
    background.setFillColor(sf::Color(150, 150, 150, 255));  // Light grey

    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::Black);
    //scoreText.setPosition(10, 10);

    heightText.setFont(font);
    heightText.setCharacterSize(24);
    heightText.setFillColor(sf::Color::Black);
    //heightText.setPosition(120, 10);

    pauseButton.setSize(sf::Vector2f(70, 30));
    pauseButton.setFillColor(sf::Color::Black);
    //pauseButton.setPosition(width - 110, 10);  // Position within the sidebar

    pauseText.setFont(font);
    pauseText.setString("PAUSE");
    pauseText.setCharacterSize(24);
    pauseText.setFillColor(sf::Color::White);
    //pauseText.setPosition(pauseButton.getPosition().x , pauseButton.getPosition().y );


}

void Sidebar::update(int score, int height, int lives , float x , float y) 
{
    scoreText.setString("Score: " + std::to_string(score));

    heightText.setString("Height: " + std::to_string(height));


    livesRects.clear();
    for (int i = 0; i < lives; ++i) 
    {
        sf::RectangleShape life(sf::Vector2f(20, 20));
        life.setFillColor(sf::Color::Red);
        life.setPosition(300 + i * 30, y+20);
        livesRects.push_back(life);
    }
    background.setPosition(x, y + 20);
    scoreText.setPosition(10, y + 20);
    heightText.setPosition(100, y + 20);
    pauseButton.setPosition(700, y + 20);
    pauseText.setPosition(700 , y + 20);

}

void Sidebar::draw(sf::RenderWindow& window)
{
    window.draw(background);
    window.draw(scoreText);
    window.draw(heightText);
    window.draw(pauseButton);
    window.draw(pauseText);
    for (auto& rect : livesRects)
    {
        window.draw(rect);
    }
}

bool Sidebar::isPaused(sf::Vector2i mousePos)
{
    return pauseButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

