#include "HelpScreen.h"
#include <iostream>

HelpScreen::HelpScreen() 
{
    if (!m_font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font\n";
    }
    m_screen.setTexture(*(Singleton::instance().getScreen(HELP_m)));

    std::vector<sf::Vector2f> positions = { sf::Vector2f(353, 100), sf::Vector2f(665, 40),sf::Vector2f(157, 265), 
        sf::Vector2f(7, 370),sf::Vector2f(523, 374),sf::Vector2f(652, 449), sf::Vector2f(4, 540),sf::Vector2f(695, 515) };

    std::string menuItems[] = { "FELL FALL" ,"THIS IS YOUR \n\n\n   HELL!",
"YOUR WAY OUT IS JUMPING UP AND AVOIDING FALLING DOWN!" ,
"you only have three precious lives",
"DON'T lose!"
,"USE THE GIFTS",
"WELL , CAN YOU STAY ALIVE?",
    "BACK"};

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

Screens_m HelpScreen::handleEvents(sf::RenderWindow& window)
{
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            window.close();
            return HELP_m;  // or a specific screen type for closing
        case sf::Event::MouseButtonReleased:
            if (event.mouseButton.button == sf::Mouse::Left) 
            {
                int mouseX = event.mouseButton.x;
                int mouseY = event.mouseButton.y;

                std::cout << "Mouse Clicked at: X: " << mouseX << ", Y: " << mouseY << std::endl;

                sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);

                if (m_backButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                {
                    Singleton::instance().getSoundManager().playSound("click"); // Play click sound

                    return MENU_m;  // Return to menu screen
                }
            }
            break;
        }
    }
    return HELP_m;
}

void HelpScreen::render(sf::RenderWindow& window) {
    window.draw(m_screen);
    window.draw(m_backButton);
    for (size_t i = 0; i < m_Texts.size(); ++i) {
        window.draw(m_Texts[i]);
    }
}
