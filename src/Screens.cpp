#include "Screens.h"

Screens::Screens() : m_back(false)
{
	m_screens[MENU_m].setTexture(*(Singleton::instance().getScreen(MENU_m)));
	m_screens[PLAY_GAME_m].setTexture(*(Singleton::instance().getScreen(PLAY_GAME_m)));
	m_screens[HELP_m].setTexture(*(Singleton::instance().getScreen(HELP_m)));
	m_screens[SETTINGS_m].setTexture(*(Singleton::instance().getScreen(SETTINGS_m)));
	m_screens[HIGH_SCOORE_m].setTexture(*(Singleton::instance().getScreen(HIGH_SCOORE_m)));
	m_screens[C1_m].setTexture(*(Singleton::instance().getScreen(C1_m)));
	m_screens[C2_m].setTexture(*(Singleton::instance().getScreen(C2_m)));


	getUpdatedScore(); // I want it when I click on the play
}

Screens::~Screens()
{
	exit(EXIT_SUCCESS);
}


void Screens::runMenu()
{
	directorScreens(MENU_m, "menu");

	while (m_window.isOpen())
	{
		sf::Event event;

		while (m_window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break;

			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					Menu_c button = getMenuButton(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
					switch (button)
					{
					case PLAY_GAME_c:  //go choose if want to play with 1 or 2 plyers
						choosePlayer();
						break;

					case HELP_c:
						helpPage();//go help page
						break;

					case SETTINGS_c:
						settingsPage(); // go to settings page
						break;

					case HIGH_SCOORE_c:// go to high scoore page
						highScorePage();
						break;

					case EXIT_c:
						m_window.close();  //exit the game 
						break;

					default:
						break;
					}
				}
				break;
			}
		}
		//if it is coming from anther bage like help, high score .....
		if (m_back == true) {
			m_back = false;
			directorScreens(MENU_m, "menu");
		}

		render(MENU_m);
	}
}

void Screens::directorScreens(const Screens_m& screen, const std::string& title)
{
	sf::Vector2u imageSize = (*(Singleton::instance().getScreen(screen))).getSize();
	m_window.create(sf::VideoMode(imageSize.x, imageSize.y), title);
}

void Screens::render(const Screens_m& screen)
{
	m_window.draw(m_screens[screen]);
	m_window.display();
	m_window.clear();
}

void Screens::getUpdatedScore()
{
	auto score = Singleton::instance().loadHighScore();
	for (int i = 0; i < NUM_OF_HIGH_SCCORES; i++)
		m_TopScore[i] = score[i]._score;
}

Menu_c Screens::getMenuButton(sf::Vector2i mousePos)
{
    if ((mousePos.x >= 410 && mousePos.x <= 660) &&
        (mousePos.y >= 380 && mousePos.y <= 440))
    {
        return PLAY_GAME_c;
    }
    else if ((mousePos.x >= 410 && mousePos.x <= 660) &&
        (mousePos.y >= 480 && mousePos.y <= 540))
    {
        return HELP_c;
    }
    else if ((mousePos.x >= 410 && mousePos.x <= 660) &&
        (mousePos.y >= 560 && mousePos.y <= 620))
    {
        return SETTINGS_c;
    }
    else if ((mousePos.x >= 410 && mousePos.x <= 660) &&
        (mousePos.y >= 650 && mousePos.y <= 710))
    {
        return HIGH_SCOORE_c;
    }
    else if ((mousePos.x >= 410 && mousePos.x <= 660) &&
        (mousePos.y >= 745 && mousePos.y <= 800))
    {
        return EXIT_c;
    }
	return Menu_c();
	
}

void Screens::choosePlayer()
{
	directorScreens(PLAY_GAME_m, "choose player");

	while (m_window.isOpen())
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					Chooseen button = getChooseButton(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
					
					if (button == ONE_PLAYER)
						playerDetails(1);
						
					else if (button == TWO_PLAYERS)
						playerDetails(2);
						
					if (button == BACK) {
						m_back = true;
						break;
					}

					
				}
			}
		}

		//to bake to the menu loop 
		if (m_back == true) {
			break;
		}
		render(PLAY_GAME_m);
	}
}

Chooseen Screens::getChooseButton(sf::Vector2i mousePos)
{
	if ((mousePos.x >= 490 && mousePos.x <= 580) &&
		 (mousePos.y >= 150 && mousePos.y <= 220))
	{
		return BACK;
	}
	else if ((mousePos.x >= 435 && mousePos.x <= 645) &&
		(mousePos.y >= 460 && mousePos.y <= 520)) 
	{
		return ONE_PLAYER;
	}
	else if ((mousePos.x >= 435 && mousePos.x <= 645) &&
		(mousePos.y >= 580 && mousePos.y <= 635))
	{
		return TWO_PLAYERS;
	}
	return Chooseen();
}

void Screens::helpPage()
{
	directorScreens(HELP_m, "help page");

	while (m_window.isOpen())
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);

					//this where the postion of bake to menu
					if ((mousePos.x >= 400 && mousePos.x <= 570)
						&& (mousePos.y >= 515 && mousePos.y <= 535)) {
						m_back = true;
						break;
					}
				}
			}
		}

		//to bake to the menu loop 
		if (m_back == true) {
			break;
		}
		render(HELP_m);
	}
}

void Screens::settingsPage()
{
	directorScreens(SETTINGS_m, "settings");

	while (m_window.isOpen())
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);

					//this where the postion of bake to menu
					if ((mousePos.x >= 540 && mousePos.x <= 755) &&
						(mousePos.y >= 495 && mousePos.y <= 540))
					{
						m_back = true;
						break;
					}
				}
			}
		}

		//to bake to the menu loop 
		if (m_back == true) {
			break;
		}
		render(SETTINGS_m);
	}
}

void Screens::highScorePage()
{
	directorScreens(HIGH_SCOORE_m, "high scoore");

	while (m_window.isOpen())
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);

					//this where the postion of bake to menu
					if ((mousePos.x >= 230 && mousePos.x <= 465) &&
						(mousePos.y >= 800 && mousePos.y <= 835)){
						m_back = true;
						break;
					}
				}
			}
		}

		//to bake to the menu loop 
		if (m_back == true) {
			break;
		}
		render(HIGH_SCOORE_m);
	}
}

void Screens::chooseCharacter()
{
	// Define the initial selected character index
	int selectedCharacterIndex = 0;

	// Define the positions and sizes of the character rectangles based on the given coordinates
	sf::FloatRect characterBounds[4] = {
		{19, 88, 171, 224},   // Character 1 bounds
		{252, 89, 164, 215},  // Character 2 bounds
		{471, 98, 175, 212},  // Character 3 bounds
		{711, 88, 177, 220}   // Character 4 bounds
	};

	// Create a rectangle shape for the selection outline
	sf::RectangleShape selectionRectangle;
	selectionRectangle.setSize(sf::Vector2f(characterBounds[0].width, characterBounds[0].height));
	selectionRectangle.setOutlineThickness(5);
	selectionRectangle.setOutlineColor(sf::Color::Red);
	selectionRectangle.setFillColor(sf::Color::Transparent);

	// Define the position for the text input area
	sf::FloatRect textInputBounds = { 456, 382, 226, 29 };

	// Create a text object to display the player's name
	sf::Font font;
	if (!font.loadFromFile("arial.ttf")) // Make sure to replace with the path to your font file
	{
		std::cerr << "Error loading font" << std::endl;
	}

	sf::Text playerNameText;
	playerNameText.setFont(font);
	playerNameText.setCharacterSize(24);
	playerNameText.setFillColor(sf::Color::White);
	playerNameText.setPosition(textInputBounds.left, textInputBounds.top);

	std::string playerName;

	// Update the position of the selection rectangle based on the current selection
	selectionRectangle.setPosition(characterBounds[selectedCharacterIndex].left, characterBounds[selectedCharacterIndex].top);

	while (m_window.isOpen())
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Right)
				{
					// Move selection to the right
					selectedCharacterIndex = (selectedCharacterIndex + 1) % 4;
				}
				else if (event.key.code == sf::Keyboard::Left)
				{
					// Move selection to the left
					selectedCharacterIndex = (selectedCharacterIndex + 3) % 4; // +3 instead of -1 to handle negative modulus
				}
				// Update the position of the selection rectangle
				selectionRectangle.setPosition(characterBounds[selectedCharacterIndex].left, characterBounds[selectedCharacterIndex].top);
				selectionRectangle.setSize(sf::Vector2f(characterBounds[selectedCharacterIndex].width, characterBounds[selectedCharacterIndex].height));
				break;
			case sf::Event::TextEntered:
				if (event.text.unicode == '\b' && !playerName.empty())
				{
					// Handle backspace
					playerName.pop_back();
				}
				else if (event.text.unicode < 128 && event.text.unicode != '\b')
				{
					// Append the entered character to the player's name
					playerName += static_cast<char>(event.text.unicode);
				}
				playerNameText.setString(playerName);
				break;
			}
		}
		m_window.draw(m_screens[C1_m]);
		m_window.draw(selectionRectangle);
		m_window.draw(playerNameText);
		m_window.display();
		m_window.clear();
	}
}


void Screens::playerDetails(const int& numberOfPlayers)
{

	if (numberOfPlayers == 1)
	{
		directorScreens(C1_m, "One player mode");
	}
	else
	{
		directorScreens(C2_m, "Two player mode");
	}

	while (m_window.isOpen())
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break;
			}
		}

		if (numberOfPlayers == 1)
		{

			chooseCharacter();
		}
		else
			render(C2_m);
		
	}
}
