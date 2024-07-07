#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <string>


// Enum representing different screen types
enum Screens_m {
    MENU_m,
    PLAY_GAME_m,
    HELP_m,
    SETTINGS_m,
    HIGH_SCOORE_m,
    C1_m,
    C2_m,
    GAME_m,
    GAME_FOR_TWO_m,
    PAUSE_m
};

// Enum representing menu options
enum Menu_c {
    PLAY_GAME_c,
    HELP_c,
    SETTINGS_c,
    HIGH_SCOORE_c,
    EXIT_c
};

// Enum representing play mode options
enum Chooseen {
    ONE_PLAYER,
    TWO_PLAYERS,
    BACK
};

// Enum representing character types
enum Characters {
    DARK_MAN_p,
    DINASOR_p,
    SHARP_p,
    WITCH_p,
    DARK_MAN_WINGS_p,
    DINASOR_WINGS_p,
    SHARP_WINGS_p,
    WITCH_WINGS_p
};

// Enum representing game effects
enum GameEffects {
    BAT_a,
    HEART_a,
    HOLE_a,
    TRAMPOLINE_a,
    WINGS_a
};

// Constants for game settings
const int MEDIUM_HEIGHT = 30;
const float BAT_SPAWN_INTERVAL = 9.0f;
const int HARD_HEIGHT = 50;
const float BLACK_HOLE_SPAWN_INTERVAL = 10.0f;
const float GIFT_SPAWN_INTERVAL = 3.0f;
const float TRAMPOLINE_SPAWN_INTERVAL = 3.0f;
const float WING_GIFT_SPAWN_INTERVAL = 9.0f;
const int STORY_SCREENS = 7;


// Abstract base class for all game objects
class GameObject {
public:
    GameObject() = default;
    virtual ~GameObject() = default;

    // Reset the position of the game object
    virtual void resetPosition(float x, float y) = 0;

    // Get the current position of the game object
    virtual sf::Vector2f getPosition() const = 0;

    // Draw the game object on the window
    virtual void draw(sf::RenderWindow& window) = 0;

    // Handle collision with another game object
    virtual void onCollision(GameObject& other) = 0;

    // Get the bounding box of the game object
    virtual sf::FloatRect getBounds() const = 0;

    // Check collision with another game object
    virtual bool checkCollision(GameObject& other) {
        return this->getBounds().intersects(other.getBounds());
    }

    // Get the type of the game object as a string
    virtual std::string getType() const = 0;

protected:
    sf::Sprite m_sprite; // Sprite representing the game object
};