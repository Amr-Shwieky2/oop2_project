#include "MenuScreen.h"
#include <iostream>

MenuScreen::MenuScreen() :
    m_titleRect(200, 50, 400, 75), 
    m_playButton(300, 200, 200, 50), // Adjusted to Y = 200
    m_helpButton(300, 275, 200, 50), // Adjusted to Y = 275
    m_settingsButton(300, 350, 200, 50), // Adjusted to Y = 350
    m_topScoresButton(300, 425, 200, 50), // Adjusted to Y = 425
    m_exitButton(300, 500, 200, 50) // Adjusted to Y = 500
{
    m_screen.setTexture(*(Singleton::instance().getScreen(MENU_m)));
    m_font.loadFromFile("arial.ttf"); // Ensure the font file path is correct

    // Initialize title text and rectangle
    sf::Text titleText;
    titleText.setFont(m_font);
    titleText.setString("        Fell Fall");
    titleText.setCharacterSize(36); // Increased font size for the title
    titleText.setFillColor(sf::Color::Black);
    titleText.setPosition(m_titleRect.left + 50, m_titleRect.top + 15); // Center text in the rectangle

    sf::RectangleShape titleRect;
    titleRect.setSize(sf::Vector2f(m_titleRect.width, m_titleRect.height));
    titleRect.setPosition(m_titleRect.left, m_titleRect.top);
    titleRect.setFillColor(sf::Color(180, 50, 50, 250)); // More vibrant color for distinction

    m_Texts.push_back(titleText);
    m_Rectangles.push_back(titleRect);

    // Initialize other button texts and rectangles
    std::vector<std::pair<sf::IntRect*, std::string>> buttons = {
        {&m_playButton, "          Play"},
        {&m_helpButton, "          Help"},
        {&m_settingsButton, "         Setting"},
        {&m_topScoresButton, "       Top Score"},
        {&m_exitButton, "          Exit"}
    };

    for (auto& button : buttons) {
        sf::Text text;
        text.setFont(m_font);
        text.setString(button.second);
        text.setCharacterSize(24); // Consistent size for menu items
        text.setFillColor(sf::Color::White);
        text.setPosition(button.first->left + 20, button.first->top + 10);

        sf::RectangleShape rect;
        rect.setSize(sf::Vector2f(button.first->width, button.first->height));
        rect.setPosition(button.first->left, button.first->top);
        rect.setFillColor(sf::Color(100, 100, 100, 200));

        m_Texts.push_back(text);
        m_Rectangles.push_back(rect);
    }
}


Screens_m MenuScreen::handleEvents(sf::RenderWindow& window) 
{
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            window.close();
            return MENU_m;  // or a specific screen type for closing
        case sf::Event::MouseButtonReleased:
            if (event.mouseButton.button == sf::Mouse::Left) 
            {
                sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
                std::cout << "Mouse clicked at: (" << mousePos.x << ", " << mousePos.y << ")" << std::endl;


                Menu_c button = getMenuButton(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

                switch (button) {
                case PLAY_GAME_c:
                    Singleton::instance().getSoundManager().playSound("click"); // Play click sound
                    return PLAY_GAME_m;
                case HELP_c:
                    Singleton::instance().getSoundManager().playSound("click"); // Play click sound
                    return HELP_m;
                case SETTINGS_c:
                    Singleton::instance().getSoundManager().playSound("click"); // Play click sound
                    return SETTINGS_m;
                case HIGH_SCOORE_c:
                    Singleton::instance().getSoundManager().playSound("click"); // Play click sound
                    return HIGH_SCOORE_m;
                case EXIT_c:
                    Singleton::instance().getSoundManager().playSound("click"); // Play click sound
                    window.close();
                    return MENU_m;  // or a specific screen type for exit
                default:
                    break;
                }
            }
            break;
        }
    }
    return MENU_m;
}

void MenuScreen::render(sf::RenderWindow& window) {
    window.draw(m_screen);
    for (size_t i = 0; i < m_Rectangles.size(); ++i) {
        window.draw(m_Rectangles[i]);
        window.draw(m_Texts[i]);
    }
}

Menu_c MenuScreen::getMenuButton(sf::Vector2i mousePos) {
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
