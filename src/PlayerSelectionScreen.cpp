#include "PlayerSelectionScreen.h"
#include <iostream>
PlayerSelectionScreen::PlayerSelectionScreen() :
    onePlayerButton(58, 174, 200, 50),    // Set size directly based on visible rectangle size
    twoPlayersButton(538, 163, 200, 50),  // Set size directly based on visible rectangle size
    backButton(309, 309, 200, 50) {       // Set size directly based on visible rectangle size


    if (!m_font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font\n";
    }

    m_screen.setTexture(*(Singleton::instance().getScreen(PLAY_GAME_m)));

    std::vector<sf::Vector2f> positions = { sf::Vector2f(58, 177), sf::Vector2f(540, 165) ,sf::Vector2f(309, 310) }; // Positions for texts and rectangles

    std::string menuItems[] = { "  One Player", "  Two Players" ,"  Go Back"};
    for (int i = 0; i < 3; ++i) {
        // Create a black rectangle below the text
        sf::RectangleShape rectangle(sf::Vector2f(200, 50)); // Set size of rectangle
        rectangle.setPosition(positions[i]); // Set position
        rectangle.setFillColor(sf::Color::Black);
        m_Rectangles.push_back(rectangle);
        
        sf::Text text(menuItems[i], m_font, 35);
        sf::FloatRect textBounds = text.getLocalBounds();
        //text.setOrigin(textBounds.width / 2, textBounds.height / 2);
        // Set position slightly above the rectangle
        text.setPosition(positions[i]);
        text.setFillColor(sf::Color::White);
        m_Texts.push_back(text);


    }
}


Screens_m PlayerSelectionScreen::handleEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            window.close();
            break;  // Added a break here to prevent fall-through
        case sf::Event::MouseButtonReleased:
            if (event.mouseButton.button == sf::Mouse::Left) {
                int mouseX = event.mouseButton.x;
                int mouseY = event.mouseButton.y;

                std::cout << "Mouse Clicked at: X: " << mouseX << ", Y: " << mouseY << std::endl;

                Chooseen button = getChooseButton(sf::Vector2i(mouseX, mouseY));
                switch (button) {
                case ONE_PLAYER:
                    Singleton::instance().getSoundManager().playSound("click");
                    return C1_m;
                case TWO_PLAYERS:
                    Singleton::instance().getSoundManager().playSound("click");
                    return C2_m;
                case BACK:
                    Singleton::instance().getSoundManager().playSound("click");
                    return MENU_m;
                default:
                    // Do nothing if no button was clicked
                    break;
                }
            }
            break;
        }
    }
    return PLAY_GAME_m;  // Stay on
}

void PlayerSelectionScreen::render(sf::RenderWindow& window) {
    window.draw(m_screen);


    for (size_t i = 0; i < m_Texts.size(); ++i) {
        window.draw(m_Rectangles[i]);
        window.draw(m_Texts[i]);
    }
}

Chooseen PlayerSelectionScreen::getChooseButton(sf::Vector2i mousePos) {
    if (onePlayerButton.contains(mousePos)) {
        return ONE_PLAYER;
    }
    else if (twoPlayersButton.contains(mousePos)) {
        return TWO_PLAYERS;
    }
    else if (backButton.contains(mousePos)) {
        return BACK;
    }
    return Chooseen();
}
