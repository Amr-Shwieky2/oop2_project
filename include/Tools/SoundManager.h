#pragma once
#include <SFML/Audio.hpp>
#include <map>
#include <string>

// Class to manage sound effects and music
class SoundManager {
public:
    SoundManager(); // Constructor
    ~SoundManager(); // Destructor

    void playSound(const std::string& name); // Play a sound effect by name
    void playMusic(); // Play the background music
    void stopMusic(); // Stop the background music
    void setMusicVolume(float volume); // Set the volume for music
    void setEffectsVolume(float volume); // Set the volume for sound effects

private:
    void loadSound(const std::string& name, const std::string& filename); // Load a sound effect

    std::map<std::string, sf::SoundBuffer> buffers; // Map of sound buffers
    std::map<std::string, sf::Sound> sounds; // Map of sound effects
    sf::Music music; // Background music
};
