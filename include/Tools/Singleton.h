#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include "SoundManager.h"
#include "LoadingManager.h"

class GameLogic;

class Singleton {
public:
    static Singleton& instance();
    SoundManager& getSoundManager();

    GameLogic& getCurrentGameLogic() { return *m_currentGameLogic; }
    void setCurrentGameLogic(std::shared_ptr<GameLogic> gameLogic);

    void setPlayerName1(const std::string& name) { m_playerName1 = name; }
    void setPlayerName2(const std::string& name) { m_playerName2 = name; }
    std::string getPlayerName1() const { return m_playerName1; }
    std::string getPlayerName2() const { return m_playerName2; }

    void setPlayerCharacter1(const int& Character = 1);
    void setPlayerCharacter2(const int& Character = 2);
    Characters getPlayerCharacter1() const { return m_playerCharacter1; };
    Characters getPlayerCharacter2() const { return m_playerCharacter2; };

private:
    Singleton();
    void fillCharacters(const int&, Characters&);

    std::string m_playerName1;
    std::string m_playerName2;
    Characters m_playerCharacter1 = DARK_MAN_p;
    Characters m_playerCharacter2 = DARK_MAN_p;

    SoundManager m_soundManager;
    std::shared_ptr<GameLogic> m_currentGameLogic;
};
