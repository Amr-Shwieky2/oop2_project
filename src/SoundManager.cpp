#include "SoundManager.h"
#include <iostream>

SoundManager::SoundManager() {
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

    if (!m_music.openFromFile("drama.ogg")) {
        std::cerr << "Failed to load music" << std::endl;
    }
    m_music.setLoop(true);
}

void SoundManager::playSound(const std::string& name) {
    if (m_sounds.find(name) != m_sounds.end()) {
        m_sounds[name].play();
    }
    else {
        std::cerr << "Sound not found: " << name << std::endl;
    }
}

void SoundManager::playMusic() {
    m_music.play();
}

void SoundManager::stopMusic() {
    m_music.stop();
}

void SoundManager::setMusicVolume(float volume) {
    m_music.setVolume(volume);
}

void SoundManager::setEffectsVolume(float volume) {
    for (auto& sound : m_sounds) {
        sound.second.setVolume(volume);
    }
}

void SoundManager::loadSound(const std::string& name, const std::string& filename) {
    sf::SoundBuffer buffer;
    if (buffer.loadFromFile(filename)) {
        m_buffers[name] = buffer;
        sf::Sound sound;
        sound.setBuffer(m_buffers[name]);
        m_sounds[name] = sound;
    }
    else {
        std::cerr << "Failed to load sound: " << filename << std::endl;
    }
}
