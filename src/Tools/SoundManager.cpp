#include "SoundManager.h"
#include <iostream>

// Constructor implementation
SoundManager::SoundManager() {
    try {
        // Load all sounds
        loadSound("burned", "burned.wav");
        loadSound("characters", "characters.wav");
        loadSound("click", "click.wav");
        loadSound("coins", "coins.wav");
        loadSound("glassshatter", "glassshatter.wav");
        loadSound("jump", "jump.wav");
        loadSound("music", "music2.ogg");
        loadSound("drama", "drama.ogg");
        loadSound("names", "names.wav");
        loadSound("rock", "rock.wav");
        loadSound("top5", "top5.wav");
        loadSound("winning", "winning.wav");

        // Set up music stream
        if (!music.openFromFile("drama.ogg")) {
            throw std::runtime_error("Failed to load music");
        }
        music.setLoop(true); // Set music to loop
    }
    catch (const std::exception& e) {
        std::cerr << "Error initializing SoundManager: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error initializing SoundManager" << std::endl;
        throw;
    }
}

// Play a sound effect by name
void SoundManager::playSound(const std::string& name) {
    try {
        if (sounds.find(name) != sounds.end()) {
            sounds[name].play();
        }
        else {
            std::cerr << "Sound not found: " << name << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error playing sound: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error playing sound" << std::endl;
        throw;
    }
}

// Play the background music
void SoundManager::playMusic() {
    try {
        music.play();
    }
    catch (const std::exception& e) {
        std::cerr << "Error playing music: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error playing music" << std::endl;
        throw;
    }
}

// Stop the background music
void SoundManager::stopMusic() {
    try {
        music.stop();
    }
    catch (const std::exception& e) {
        std::cerr << "Error stopping music: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error stopping music" << std::endl;
        throw;
    }
}

// Set the volume for music
void SoundManager::setMusicVolume(float volume) {
    try {
        music.setVolume(volume);
    }
    catch (const std::exception& e) {
        std::cerr << "Error setting music volume: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error setting music volume" << std::endl;
        throw;
    }
}

// Set the volume for sound effects
void SoundManager::setEffectsVolume(float volume) {
    try {
        for (auto& sound : sounds) {
            sound.second.setVolume(volume);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error setting effects volume: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error setting effects volume" << std::endl;
        throw;
    }
}

// Load a sound effect
void SoundManager::loadSound(const std::string& name, const std::string& filename) {
    try {
        sf::SoundBuffer buffer;
        if (buffer.loadFromFile(filename)) {
            buffers[name] = buffer;
            sf::Sound sound;
            sound.setBuffer(buffers[name]);
            sounds[name] = sound;
        }
        else {
            throw std::runtime_error("Failed to load sound: " + filename);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error loading sound: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error loading sound" << std::endl;
        throw;
    }
}

// Destructor implementation
SoundManager::~SoundManager() {
    try {
        // Clean up if necessary
    }
    catch (const std::exception& e) {
        std::cerr << "Error destroying SoundManager: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Unknown error destroying SoundManager" << std::endl;
    }
}
