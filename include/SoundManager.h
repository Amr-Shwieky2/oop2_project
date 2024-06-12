#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <SFML/Audio.hpp>
#include <map>
#include <string>

class SoundManager
{
public:
    SoundManager();
    ~SoundManager();

    void playSound(const std::string& name);
    void playMusic();
    void stopMusic();

private:
    std::map<std::string, sf::SoundBuffer> buffers;
    std::map<std::string, sf::Sound> sounds;
    sf::Music music;

    void loadSound(const std::string& name, const std::string& filename);
};

#endif
