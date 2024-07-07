#include "Singleton.h"
#include <fstream>
#include <iostream>

Singleton::Singleton() {
    
}

Singleton& Singleton::instance() {
    static Singleton instance;
    return instance;
}

void Singleton::setPlayerCharacter1(const int& Character)
{
    m_characterNamber1 = Character;
    fillCharacters(Character, m_playerCharacter1);
}

void Singleton::setPlayerCharacter2(const int& Character)
{
    m_characterNamber2 = Character;
    fillCharacters(Character, m_playerCharacter2);
}

void Singleton::fillCharacters(const int& Character, Characters& player)
{
    switch (Character)
    {
    case 0:
        player = DARK_MAN_p;
        break;
    case 1:
        player = DINASOR_p;
        break;
    case 2:
        player = WITCH_p;
        break;
    case 3:
        player = SHARP_p;
        break;
    case 4:
        player = DARK_MAN_WINGS_p;
        break;
    case 5:
        player = DINASOR_WINGS_p;
        break;
    case 6:
        player = WITCH_WINGS_p;
        break;
    case 7:
        player = SHARP_WINGS_p;
        break;

    default:
        break;
    }
}

void Singleton::setCurrentGameLogic(std::shared_ptr<GameLogic> gameLogic)
{
    m_currentGameLogic = gameLogic;
}


SoundManager& Singleton::getSoundManager() {
    return m_soundManager;
}

