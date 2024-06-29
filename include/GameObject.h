#pragma once
#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>

// screens in all the game
enum Screens_m { MENU_m, PLAY_GAME_m, HELP_m, SETTINGS_m, HIGH_SCOORE_m, C1_m, C2_m, GAME_m };

// screens in the menu
enum Menu_c { PLAY_GAME_c, HELP_c, SETTINGS_c, HIGH_SCOORE_c, EXIT_c };

// screens in the play mode
enum Chooseen { ONE_PLAYER, TWO_PLAYERS, BACK };

enum GameEffects{ BAT_a, HEART_a, HOLE_a,TRAMPOLINE_a, WINGS_a, 
                    DARK_MAN_p, DINASOR_p, SHARP_p, WITCH_p};

enum Type { NORMAL, MOVING, BREAKABLE };

class GameObject {
public:
    GameObject() {};
    virtual ~GameObject() = default;

    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void update(float deltaTime) = 0;
    virtual void resetPosition(float x, float y) = 0;
    virtual sf::FloatRect getBounds() const = 0;
    virtual sf::Vector2f getPosition() const = 0;

protected:
    sf::Sprite m_sprite;
};