#pragma once
#include <SFML/Audio.hpp>
#include <map>
#include <string>

class SoundManager {
public:
    SoundManager();
    ~SoundManager() = default;
    void playSound(const std::string& name);
    void playMusic();
    void stopMusic();
    void setMusicVolume(float volume);
    void setEffectsVolume(float volume);

private:
    void loadSound(const std::string& name, const std::string& filename);

    std::map<std::string, sf::SoundBuffer> m_buffers;
    std::map<std::string, sf::Sound> m_sounds;
    sf::Music m_music;
};
