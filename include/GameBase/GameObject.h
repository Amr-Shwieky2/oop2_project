#pragma once
#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>

// screens in all the game
enum Screens_m { MENU_m, PLAY_GAME_m, HELP_m, SETTINGS_m,
                    HIGH_SCOORE_m, C1_m, C2_m, GAME_m, GAME_FOR_TWO_m, PAUSE_m};

// screens in the menu
enum Menu_c { PLAY_GAME_c, HELP_c, SETTINGS_c, HIGH_SCOORE_c, EXIT_c };

// screens in the play mode
enum Chooseen { ONE_PLAYER, TWO_PLAYERS, BACK };

enum Characters{ DARK_MAN_p, DINASOR_p, SHARP_p, WITCH_p };

enum GameEffects{ BAT_a, HEART_a, HOLE_a,TRAMPOLINE_a, WINGS_a };

const int MEDIUM_HEIGHT = 30;
const float BAT_SPAWN_INTERVAL = 5.0f;
const int HARD_HEIGHT = 50;
const float BLACK_HOLE_SPAWN_INTERVAL = 10.0f;
const float GIFT_SPAWN_INTERVAL = 3.0f;
const float TRAMPOLINE_SPAWN_INTERVAL = 3.0f;
const float WING_GIFT_SPAWN_INTERVAL = 9.0f;
const int STORY_SCREENS = 7;


class GameObject {
public:
    GameObject() = default;
    virtual ~GameObject() = default;

    virtual void resetPosition(float x, float y) = 0;
    virtual sf::Vector2f getPosition() const = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void onCollision(GameObject& other) = 0;
    virtual sf::FloatRect getBounds() const = 0;
    virtual bool checkCollision(GameObject& other) {
        return this->getBounds().intersects(other.getBounds());
    }

    virtual std::string getType() const = 0; 

protected:
    sf::Sprite m_sprite;
};