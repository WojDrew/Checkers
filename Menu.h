#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class AppManager;

class Menu
{
	AppManager* applicaton;

	sf::Texture* teksturaButton;
	sf::Texture* teksturaNewGame;
	sf::Texture* teksturaSave;
	sf::Texture* teksturaLoad;
	sf::Texture* teksturaExit;

	sf::Texture* teksturaButtonTouch;
	sf::Texture* teksturaNewGameTouch;
	sf::Texture* teksturaSaveTouch;
	sf::Texture* teksturaLoadTouch;
	sf::Texture* teksturaExitTouch;

	sf::Sprite* button;
	sf::Sprite* newGame;
	sf::Sprite* save;
	sf::Sprite* load;
	sf::Sprite* exit;

	bool expanded;
	bool touched;
public:
	Menu(AppManager* appman);
	void show();
	void menuClicked(int x, int y);
	void setDefault();
	void menuTouch(int x, int y);
	~Menu();
};

