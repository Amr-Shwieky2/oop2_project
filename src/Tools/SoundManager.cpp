#include "SoundManager.h"
#include <iostream>

SoundManager::SoundManager() 
{
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

    m_effectDot.setPosition(350 + 50 * 2 - 10, 426 - 5);
    m_effectDotPosition.x = 350 + 50 * 2 - 10;
    m_effectDotPosition.y = 426 - 5;

    // Optionally, set up music streams if they need to be looped or controlled separately
    if (!music.openFromFile("drama.ogg"))
    {
        std::cerr << "Failed to load music" << std::endl;
    }
    music.setLoop(true); // Setting music to loop
}

sf::Vector2f SoundManager::geteffectDotPosition() const {
    return m_effectDotPosition;
}

void SoundManager::seteffectDotPosition(const sf::Vector2f& position) {
    m_effectDot.setPosition(position);
    m_effectDotPosition = position;
}
void SoundManager::playSound(const std::string& name) 
{
    if (sounds.find(name) != sounds.end())
    {
        sounds[name].play();
    }
    else
    {
        std::cerr << "Sound not found: " << name << std::endl;
    }
}

void SoundManager::playMusic()
{
    music.play();
}

void SoundManager::stopMusic()
{
    music.stop();
}

void SoundManager::setMusicVolume(float volume)
{
    music.setVolume(volume);
}

void SoundManager::resetButton(float x, float y)
{
    m_effectDot.setPosition(x, y);
    m_effectDotPosition = sf::Vector2f(x, y); // Save the position
    std::cout << m_effectDot.getPosition().x << " " << m_effectDot.getPosition().y;
}



void SoundManager::setEffectsVolume(float volume)
{
    for (auto& sound : sounds)
    {
        sound.second.setVolume(volume);
    }
}

void SoundManager::loadSound(const std::string& name, const std::string& filename)
{
    sf::SoundBuffer buffer;
    if (buffer.loadFromFile(filename))
    {
        buffers[name] = buffer;
        sf::Sound sound;
        sound.setBuffer(buffers[name]);
        sounds[name] = sound;
    }
    else {
        std::cerr << "Failed to load sound: " << filename << std::endl;
    }
}

SoundManager::~SoundManager() {}
