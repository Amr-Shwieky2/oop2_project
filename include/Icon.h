#pragma once
#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>

// screens in all the game
enum Screens_m { MENU_m, PLAY_GAME_m, HELP_m, SETTINGS_m, HIGH_SCOORE_m, C1_m, C2_m};

// screens in the menu
enum Menu_c { PLAY_GAME_c, HELP_c, SETTINGS_c, HIGH_SCOORE_c, EXIT_c };

// screens in the play mode
enum Chooseen { ONE_PLAYER, TWO_PLAYERS, BACK };

class Icon
{
public:
	Icon() = default;

private:

};
