#include "Menu.h"
#include "AppManager.h"


Menu::Menu(AppManager* appman)
{
	this->applicaton = appman;
	this->expanded = false;
	this->touched = false;

	this->button = new sf::Sprite();
	this->newGame = new sf::Sprite();
	this->save = new sf::Sprite();
	this->load = new sf::Sprite();
	this->exit = new sf::Sprite();

	this->teksturaButton = new sf::Texture();
	this->teksturaButton->loadFromFile("Grafika/menu.png");
	this->teksturaSave = new sf::Texture();
	this->teksturaSave->loadFromFile("Grafika/save.png");
	this->teksturaLoad = new sf::Texture();
	this->teksturaLoad->loadFromFile("Grafika/load.png");
	this->teksturaNewGame = new sf::Texture();
	this->teksturaNewGame->loadFromFile("Grafika/newGame.png");
	this->teksturaExit = new sf::Texture();
	this->teksturaExit->loadFromFile("Grafika/exit.png");

	this->teksturaButtonTouch = new sf::Texture();
	this->teksturaButtonTouch->loadFromFile("Grafika/menuTouch.png");
	this->teksturaSaveTouch = new sf::Texture();
	this->teksturaSaveTouch->loadFromFile("Grafika/saveTouch.png");
	this->teksturaLoadTouch = new sf::Texture();
	this->teksturaLoadTouch->loadFromFile("Grafika/loadTouch.png");
	this->teksturaNewGameTouch = new sf::Texture();
	this->teksturaNewGameTouch->loadFromFile("Grafika/newGameTouch.png");
	this->teksturaExitTouch = new sf::Texture();
	this->teksturaExitTouch->loadFromFile("Grafika/exitTouch.png");

	this->setDefault();

	this->button->setPosition(0, 0);
	this->newGame->setPosition(0, 51);
	this->save->setPosition(0, 102);
	this->load->setPosition(0, 153);
	this->exit->setPosition(0, 204);
}

void Menu::setDefault()
{
	this->button->setTexture(*teksturaButton);
	this->newGame->setTexture(*teksturaNewGame);
	this->save->setTexture(*teksturaSave);
	this->load->setTexture(*teksturaLoad);
	this->exit->setTexture(*teksturaExit);
}

void Menu:: menuClicked(int x, int y)
{
	if (this->expanded)
	{
		this->expanded = false;
		if (y > 51 && y < 101)
			this->applicaton->defaultBoard();
		else if (y > 100 && y < 156)
			this->applicaton->save();
		else if (y > 155 && y < 201)
			this->applicaton->load();
		else if (y > 204 && y < 255)
			this->applicaton->getWindow()->close();
	}
	else if(y < 50)
	{
		this->expanded = true;
	}
}

void Menu::menuTouch(int x, int y)
{

	if (y < 50)
		this->button->setTexture(*this->teksturaButtonTouch);
	else if (y > 51 && y < 101)
		this->newGame->setTexture(*this->teksturaNewGameTouch);
	else if (y > 102 && y < 152)
		this->save->setTexture(*this->teksturaSaveTouch);
	else if (y > 153 && y < 203)
		this->load->setTexture(*this->teksturaLoadTouch);
	else if (y > 204 && y < 255)
		this->exit->setTexture(*this->teksturaExitTouch);
	else
	{
		this->setDefault();
	}
	if (x > 100 || y > 255)
	{
		this->setDefault();
		this->expanded = false;
	}
		//this->touched == true;
	
}

void Menu::show()
{
	this->applicaton->getWindow()->draw(*this->button);
	if (this->expanded)
	{
		this->applicaton->getWindow()->draw(*this->newGame);
		this->applicaton->getWindow()->draw(*this->save);
		this->applicaton->getWindow()->draw(*this->load);
		this->applicaton->getWindow()->draw(*this->exit);
	}
}

Menu::~Menu()
{
	delete this->button;
	delete this->newGame;
	delete this->save;
	delete this->load;
}
