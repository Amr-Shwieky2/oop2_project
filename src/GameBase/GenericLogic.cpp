#include "GenericLogic.h"
#include <iostream>

GenericLogic::GenericLogic() : m_scoreBackground(sf::Vector2f(300.0f, 100.0f))
{
    if (!m_font.loadFromFile("arial.ttf")) {
        std::cerr << "Couldn't load the font!" << std::endl;
        std::exit(-1);
    }
    m_scoreBackground.setFillColor(sf::Color::Black);
    m_scoreText.setFont(m_font);
    m_scoreText.setCharacterSize(24);
    m_scoreText.setFillColor(sf::Color::White);
}

void GenericLogic::initialize(sf::RenderWindow& window, Player& player, Map& map)
{
    window.setFramerateLimit(60);
    map.initialize(window);
    player.resetPosition(map.getPlayerStartX(), map.getPlayerStartY());
}

void GenericLogic::update(float deltaTime, sf::RenderWindow& window,
    Player& player, Map& map, Sidebar& bar, bool& end)
{
    
    map.collision(player);
    map.update(deltaTime, window, player);

    CenterView(window, player);
    isFail(player, end);
    bar.update(map.getScore(), player.getLives());
}

void GenericLogic::CenterView(sf::RenderWindow& window, Player& player)
{
    sf::View view = window.getView();
    view.setCenter(view.getCenter().x, player.getPosition().y);
    window.setView(view);
}

void GenericLogic::render(sf::RenderWindow& window, Player& player,
    Map& map, Sidebar& bar, sf::Sprite& screen)
{
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

void GenericLogic::saveState(sf::Vector2f& savedPlayerPosition,
    float& savedPlayerVelocity,
    std::vector<Map::PlatformState>& savedPlatformStates,
    std::vector<Map::ObjectState>& savedObjectStates,
    Player& player, Map& map)
{
    savedPlayerPosition = player.getPosition();
    savedPlayerVelocity = player.getVelocity();
    savedPlatformStates = map.getPlatformStates();
    savedObjectStates = map.getObjectStates();
}

void GenericLogic::restoreState(sf::Vector2f& savedPlayerPosition,
    float& savedPlayerVelocity,
    std::vector<Map::PlatformState>& savedPlatformStates,
    std::vector<Map::ObjectState>& savedObjectStates,
    Player& player, Map& map)
{
    player.resetPosition(savedPlayerPosition.x, savedPlayerPosition.y);
    player.setVelocity(savedPlayerVelocity);

    map.setPlatformStates(savedPlatformStates);
    map.setObjectStates(savedObjectStates);
}

void GenericLogic::isFail(const Player& player, bool& end)
{
    if (player.hasFallen() || player.getLives() <= 0) {
        end = true;
    }
}

void GenericLogic::showEndBadge(sf::RenderWindow& window,
    const std::string& message, const bool& end)
{
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
