#pragma once

#include "BaseSidebar.h"

class TwoPlayerSidebar : public BaseSidebar {
public:
    TwoPlayerSidebar(float width, float height);

    void update(int, int) {};
    void update(int score1, int lives1, int score2, int lives2);
    void draw(sf::RenderWindow& window) override;

private:
    sf::Text m_scoreText2;
    std::vector<sf::Sprite> m_livesSprites2;
};
