#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <map>
#include <string>

class SoundManager {
public:
    SoundManager();
    ~SoundManager();
    void playSound(const std::string& name);
    void playMusic();
    void stopMusic();
    void setMusicVolume(float volume);
    void setEffectsVolume(float volume);
    void resetButton(float x, float y);
    sf::Vector2f geteffectDotPosition() const;
    void seteffectDotPosition(const sf::Vector2f& position);


private:
    void loadSound(const std::string& name, const std::string& filename);

    std::map<std::string, sf::SoundBuffer> buffers;
    std::map<std::string, sf::Sound> sounds;
    sf::Music music;
    sf::CircleShape m_effectDot;
    sf::Vector2f m_effectDotPosition ;


};

