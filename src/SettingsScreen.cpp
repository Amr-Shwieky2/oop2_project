#include "SettingsScreen.h"
#include <iostream>

SettingsScreen::SettingsScreen() :
    m_backButton(540, 495, 755 - 540, 540 - 495),
    m_musicVolume(50), // Initial volume set to 50%
    m_effectsVolume(50) // Initial volume set to 50%
{
    if (!m_font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font\n";
    }
    m_screen.setTexture(*(Singleton::instance().getScreen(SETTINGS_m)));

    // Initialize the effects volume bar
    m_effectsBar.setSize(sf::Vector2f(200, 10)); // Increased height
    m_effectsBar.setFillColor(sf::Color::White);
    m_effectsBar.setPosition(350, 318); // Updated position

    // Initialize the effects volume dot
    m_effectsDot.setRadius(10);
    m_effectsDot.setFillColor(sf::Color::Red);
    m_effectsDot.setPosition(350 + m_effectsVolume * 2 - 10, 318 - 5); // Updated position based on volume

    // Initialize the music volume bar
    m_musicBar.setSize(sf::Vector2f(200, 10)); // Increased height
    m_musicBar.setFillColor(sf::Color::White);
    m_musicBar.setPosition(350, 426); // Updated position

    // Initialize the music volume dot
    m_musicDot.setRadius(10);
    m_musicDot.setFillColor(sf::Color::Red);
    m_musicDot.setPosition(350 + m_musicVolume * 2 - 10, 426 - 5); // Updated position based on volume

    m_BackGround.setSize(sf::Vector2f(500, 400));
    m_BackGround.setOutlineThickness(5);
    m_BackGround.setOutlineColor(sf::Color::Red);
    m_BackGround.setFillColor(sf::Color::Black);
    m_BackGround.setPosition(150, 150);

    m_backButtonShape.setSize(sf::Vector2f(100, 50));  // Size based on your existing IntRect
    m_backButtonShape.setPosition(540, 495);  // Position
    m_backButtonShape.setFillColor(sf::Color::Red);  // Color
    m_backButtonShape.setOutlineColor(sf::Color::White);  // Outline color for better visibility
    m_backButtonShape.setOutlineThickness(2);  // Outline thickness

    std::vector<sf::Vector2f> positions = { sf::Vector2f(290, 200), sf::Vector2f(160, 300) ,sf::Vector2f(185, 410) ,sf::Vector2f(560, 505 )}; // Positions for texts and rectangles

    std::string menuItems[] = { "--SOUND SETTINGS--", "SOUND EFFECTS" ,"MUSIC" , "BACK"};
    for (int i = 0; i < 4; ++i) {
        sf::Text text(menuItems[i], m_font, 25);
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setPosition(positions[i]);
        text.setFillColor(sf::Color::White);
        m_Texts.push_back(text);
    }
    // Set initial volumes
    /*Singleton::instance().getSoundManager().playMusic();
    Singleton::instance().getSoundManager().setMusicVolume(m_musicVolume);
    Singleton::instance().getSoundManager().setEffectsVolume(m_effectsVolume);*/
}

Screens_m SettingsScreen::handleEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            window.close();
            return SETTINGS_m;  // or a specific screen type for closing
        case sf::Event::MouseButtonReleased:
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
                //if (m_backButton.contains(mousePos)) {
                //    //Singleton::instance().getSoundManager().playSound("click"); // Uncomment to play click sound
                //    return MENU_m;  // Return to menu screen
                //}
                if (m_effectsBar.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    // Correct calculation of volume based on new bar position
                    m_effectsVolume = (mousePos.x - m_effectsBar.getPosition().x) / (m_effectsBar.getSize().x * 0.01);
                    m_effectsDot.setPosition(m_effectsBar.getPosition().x + m_effectsVolume * 2 - 10, m_effectsBar.getPosition().y - 5);
                    updateVolume();
                }
                if (m_backButtonShape.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    // Play click sound if necessary
                    //Singleton::instance().getSoundManager().playSound("click");
                    return MENU_m;  // Return to the menu screen
                }
                if (m_musicBar.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    // Correct calculation of volume based on new bar position
                    m_musicVolume = (mousePos.x - m_musicBar.getPosition().x) / (m_musicBar.getSize().x * 0.01);
                    m_musicDot.setPosition(m_musicBar.getPosition().x + m_musicVolume * 2 - 10, m_musicBar.getPosition().y - 5);
                    updateVolume();
                }
            }
            break;
        }
    }
    return SETTINGS_m;
}


void SettingsScreen::render(sf::RenderWindow& window) {
    window.draw(m_screen);
    window.draw(m_BackGround);
    window.draw(m_effectsBar);
    window.draw(m_effectsDot);
    window.draw(m_musicBar);
    window.draw(m_musicDot);
    window.draw(m_backButtonShape);


    for (size_t i = 0; i < m_Texts.size(); ++i) {
        window.draw(m_Texts[i]);
    }
}

void SettingsScreen::updateVolume() {
    Singleton::instance().getSoundManager().setMusicVolume(m_musicVolume);
    Singleton::instance().getSoundManager().setEffectsVolume(m_effectsVolume);
}
