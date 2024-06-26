#include "Singleton.h"
#include <fstream>
#include <iostream>

Singleton::Singleton() {
    loadTextures();
}

Singleton& Singleton::instance() {
    static Singleton instance;
    return instance;
}

sf::Texture* Singleton::getScreen(const int& screen) {
    if (screen < 0 || screen >= NUM_OF_SCREENS) {
        throw GameException("Screen index out of range");
    }
    return &m_screens[screen];
}

void Singleton::loadTextures() {
    try {
        if (!m_screens[MENU_m].loadFromFile("menu.jpg"))
            throw GameException("Failed to load menu.jpg");
        if (!m_screens[PLAY_GAME_m].loadFromFile("choose.jpg"))
            throw GameException("Failed to load choose.jpg");
        if (!m_screens[HELP_m].loadFromFile("help.jpg"))
            throw GameException("Failed to load help.jpg");
        if (!m_screens[SETTINGS_m].loadFromFile("setting.jpg"))
            throw GameException("Failed to load setting.jpg");
        if (!m_screens[HIGH_SCOORE_m].loadFromFile("highSccores.jpg"))
            throw GameException("Failed to load highScores.jpg");
        if (!m_screens[C1_m].loadFromFile("chooseCharacters1.jpg"))
            throw GameException("Failed to load chooseCharacters1.jpg");
        if (!m_screens[C2_m].loadFromFile("chooseCharacters2.jpg"))
            throw GameException("Failed to load chooseCharacters2.jpg");
        if (!m_screens[GAME_m].loadFromFile("background.jpg"))
            throw GameException("Failed to load background.jpg");
    }
    catch (const std::exception& e) {
        std::cerr << "Error loading textures: " << e.what() << std::endl;
        throw;
    }
}

const std::vector<high_score>& Singleton::loadHighScore() {
    std::string file = "highScore.txt";
    std::ifstream input_score(file);//input file 

    //checks if the file was successfully opened
    if (!input_score.is_open()) {
        throw GameException("Could not open highScore.txt");
    }

    m_listScore.clear();
    std::string name;
    int score;
    //reads pairs of values from the file
    while (input_score >> name >> score) {
        if (input_score.fail()) {
            throw GameException("Error reading high scores");
        }
        m_listScore.push_back(high_score{ name, score });
    }

    input_score.close();

    // Debugging output
    for (const auto& hs : m_listScore) {
        std::cout << "Loaded high score: " << hs._name << " " << hs._score << std::endl;
    }

    return m_listScore;
}


//
//const std::vector<high_score>& Singleton::loadHighScore() {
//    std::string file = "highScore.txt";
//    std::ifstream input_score(file);
//
//    if (!input_score.is_open()) {
//        throw GameException("Could not open highScore.txt");
//    }
//
//    m_listScore.clear();
//    while (!input_score.eof()) {
//        high_score hs;
//        if (!(input_score >> hs._name >> hs._score)) {
//            throw GameException("Error reading high scores");
//        }
//        m_listScore.push_back(hs);
//    }
//    input_score.close();
//    return m_listScore;
//}
//
//void Singleton::updateHighScore(const std::string& playerName, int playerScore) {
//
//    // Check if the new score should be added to the high scores
//    if (m_listScore.size() < NUM_OF_HIGH_SCORES || playerScore > m_listScore.back()._score) {
//        // Insert new score
//        m_listScore.emplace_back(high_score{ playerScore, playerName });
//
//        // Sort the m_listScore in descending order
//        std::sort(m_listScore.begin(), m_listScore.end(), [](const high_score& a, const high_score& b) {
//            return a._score > b._score;
//            });
//
//        // If we have more than the maximum number of high m_listScore, remove the smallest one
//        if (m_listScore.size() > NUM_OF_HIGH_SCORES) {
//            m_listScore.pop_back();
//        }
//
//        // Clear the file and write updated m_listScore
//        //std::ofstream ofs("highScore.txt", std::ofstream::out | std::ofstream::trunc);
//
//        std::ofstream output_score("highScore.txt", std::ofstream::trunc); // Open in truncate mode to clear the file
//        if (!output_score) {
//            throw GameException("Could not open highScore.txt for writing");
//        }
//
//        for (const auto& score : m_listScore) {
//            output_score << score._name << std::endl << score._score << std::endl;
//        }
//        output_score.close();
//
//    
//    }
//
//}
void Singleton::updateHighScore(const std::string& playerName, int playerScore) {
    try {
        // Load current high scores
        loadHighScore();

        // Insert new score
        m_listScore.push_back(high_score{ playerName, playerScore }); //////v

        for (const auto& hs : m_listScore) {
            std::cout << "Loaded high score: " << hs._name << hs._score << std::endl;
        }

        // Sort the m_listScore in descending order
        std::sort(m_listScore.begin(), m_listScore.end(), [](const high_score& a, const high_score& b) {
            return a._score > b._score; // Descending order
            });

        for (const auto& hs : m_listScore) {
            std::cout << "Loaded high score: " << hs._name << " " << hs._score << std::endl;///v
        }

        // If we have more than the maximum number of high scores, remove the lowest one
        if (m_listScore.size() >= NUM_OF_HIGH_SCORES) {
            m_listScore.pop_back(); // Remove the last element, which is the lowest score due to sorting //////vvvvvv
        }

        for (const auto& hs : m_listScore) {
            std::cout << "in vector: " << hs._name << " " << hs._score << std::endl;///v
        }

        // Write updated m_listScore to file
        std::ofstream output_score("highScore.txt", std::ofstream::trunc); //  clears the existing content of the file
        if (!output_score) {
            throw GameException("Could not open highScore.txt for writing");
        }

        for (const auto& score : m_listScore) {
            output_score << score._name << " " << score._score << std::endl;
        }


        output_score.close();
        std::cout << "High scores updated successfully." << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error updating high scores: " << e.what() << std::endl;
        throw;
    }
}



SoundManager& Singleton::getSoundManager() {
    return m_soundManager;
}

