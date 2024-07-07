#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include "SoundManager.h"
#include "LoadingManager.h"

class TwoPlayerLogic;
class GameLogic;

// Singleton class to manage shared game resources and state
class Singleton {
public:
    // Get the singleton instance
    static Singleton& instance();

    // Get the sound manager
    SoundManager& getSoundManager();

    // Get the current game logic
    GameLogic& getCurrentGameLogic();

    // Set the current game logic
    void setCurrentGameLogic(std::shared_ptr<GameLogic> gameLogic);

    // Get the current game logic
    TwoPlayerLogic& getCurrentTwoGameLogic();

    // Set the current game logic
    void setCurrentTwoGameLogic(std::shared_ptr<TwoPlayerLogic> gameLogic);

    // Player name setters and getters
    void setPlayerName1(const std::string& name);
    void setPlayerName2(const std::string& name);
    std::string getPlayerName1() const;
    std::string getPlayerName2() const;

    // Player character setters and getters
    void setPlayerCharacter1(const int& Character);
    void setPlayerCharacter2(const int& Character);
    Characters getPlayerCharacter1() const;
    Characters getPlayerCharacter2() const;

    int getCharacterNamber1() const;
    int getCharacterNamber2() const;


    int getMode() const { return m_modePlayer; };
    void setMode(int mode) { m_modePlayer = mode; };

private:
    // Private constructor
    Singleton();

    // Helper function to set player characters based on character index
    void fillCharacters(const int&, Characters&);

    // Player names
    std::string m_playerName1;
    std::string m_playerName2;

    // Player characters
    Characters m_playerCharacter1 = DARK_MAN_p;
    Characters m_playerCharacter2 = DARK_MAN_p;

    // Character indices
    int m_characterNamber1;
    int m_characterNamber2;

    // Sound manager instance
    SoundManager m_soundManager;

    // Current game logic instance
    std::shared_ptr<GameLogic> m_currentGameLogic;
    std::shared_ptr<TwoPlayerLogic> m_currentTwoGameLogic;

    int m_modePlayer;
};
