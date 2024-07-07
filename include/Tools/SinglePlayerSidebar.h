#pragma once

#include "BaseSidebar.h"

class SinglePlayerSidebar : public BaseSidebar {
public:
    SinglePlayerSidebar(float width, float height);

    void update(int score, int lives) override;
    void draw(sf::RenderWindow& window) override;
private:
    std::vector<high_score> m_highScore; // List of high scores
    int findNextHigherScore(int currentScore); // Find the next higher score to beat
};
