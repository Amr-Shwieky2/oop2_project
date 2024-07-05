#include "TwoPlayerLogic.h"

TwoPlayerLogic::TwoPlayerLogic()
    :
    m_leftView(sf::FloatRect(0, 0, 800, 600)), // Assuming default size
    m_rightView(sf::FloatRect(800, 0, 800, 600)), // Assuming default size
    m_line(sf::Vector2f(2, 600)) // Assuming default height
{
    m_leftView.setViewport(sf::FloatRect(0, 0, 0.5f, 1.0f));
    m_rightView.setViewport(sf::FloatRect(0.5f, 0, 0.5f, 1.0f));
    m_line.setFillColor(sf::Color::Red);
    m_line.setPosition(800, 0); // Assuming default width
}

void TwoPlayerLogic::initializeViewsAndLine(sf::RenderWindow& window)
{
    int x = window.getSize().x;
    int y = window.getSize().y;
    window.create(sf::VideoMode(x * 2, y), "Game Window");
    m_leftView.setSize(sf::Vector2f(x, y));
    m_rightView.setSize(sf::Vector2f(x, y));
    m_rightView.setCenter(sf::Vector2f(x * 1.5f, y / 2));

    m_line.setSize(sf::Vector2f(2, y));
    m_line.setPosition(x, 0);

    m_leftLogic.initialize(window);
    m_rightLogic.initialize(window);
}

Screens_m TwoPlayerLogic::handleEvents(sf::RenderWindow& window)
{
    initializeViewsAndLine(window);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = m_clock.restart().asSeconds();

        // Handle events and update logic for the left player
        m_leftLogic.handleEvents(window);
        m_leftLogic.update(deltaTime, window);

        // Handle events and update logic for the right player
        m_rightLogic.handleEvents(window);
        m_rightLogic.update(deltaTime, window);

        render(window);
    }

    return GAME_m;
}

void TwoPlayerLogic::render(sf::RenderWindow& window)
{
    window.clear();

    // Draw the left view
    window.setView(m_leftView);
    m_leftLogic.render(window);

    // Draw the right view
    window.setView(m_rightView);
    m_rightLogic.render(window);

    // Draw the separating line in the default view
    window.setView(window.getDefaultView());
    window.draw(m_line);

    window.display();
}