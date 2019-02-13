#include "AppManager.h"
#include <iostream>
#include <fstream>
#define BLACK 1
#define WHITE 2


AppManager::AppManager()
{
	this->oknoAplikacji = new sf::RenderWindow(sf::VideoMode(1250, 1000, 32), "Warcaby");
	this->currentMarked = nullptr;
	this->menu = new Menu(this);
	this->gameMan = new GameManager(this);

	this->board = new sf::Sprite();
	this->leftPanel = new sf::Sprite();
	this->rightPanel = new sf::Sprite();
	this->mark = new sf::Sprite();

	sf::Texture* tekstura = new sf::Texture();
	tekstura->loadFromFile("Grafika/board.jpg");
	sf::Texture* tekstura2 = new sf::Texture();
	tekstura2->loadFromFile("Grafika/white.jpg");
	sf::Texture* tekstura3 = new sf::Texture();
	tekstura3->loadFromFile("Grafika/black.jpg");
	sf::Texture* tekstura4 = new sf::Texture();
	tekstura4->loadFromFile("Grafika/ramka.png");

	this->board->setTexture(*tekstura);
	this->leftPanel->setTexture(*tekstura2);
	this->rightPanel->setTexture(*tekstura3);
	this->mark->setTexture(*tekstura4);

	this->board->setPosition(125, 0);
	this->leftPanel->setPosition(1125, 0);
	this->rightPanel->setPosition(0, 0);

	this->defaultBoard();
}

void AppManager::defaultBoard()
{
	this->gameMan->restart();
	std::ifstream plik;
	plik.open("plansza.txt");
	for (int i = 0; i < 24; i++)
	{
		if (i < 12)
		{
			int x, y;
			this->pawns[i] = new Pawn(BLACK);
			plik >> x >> y;
			this->pawns[i]->setPosition(x, y);
		}
		else
		{
			int x, y;
			this->pawns[i] = new Pawn(WHITE);
			plik >> x >> y;
			this->pawns[i]->setPosition(x, y);
		}
	}
	plik.close();
}

void AppManager::display()
{
	while (this->oknoAplikacji->isOpen())
	{
		this->oknoAplikacji->draw(*board);
		this->oknoAplikacji->draw(*leftPanel);
		this->oknoAplikacji->draw(*rightPanel);
		this->menu->show();
		if(currentMarked != nullptr)
			this->oknoAplikacji->draw(*mark);

		for (int i = 0; i < 24; i++)
				this->oknoAplikacji->draw(*this->pawns[i]->getSprite());

		sf::Event zdarzenie;
		while (this->oknoAplikacji->pollEvent(zdarzenie))
		{
			if (zdarzenie.type == sf::Event::Closed)
				this->oknoAplikacji->close();
			if (zdarzenie.type == sf::Event::MouseButtonPressed && zdarzenie.mouseButton.button == sf::Mouse::Left)
			{
				sf::Vector2i position = sf::Mouse::getPosition(*this->oknoAplikacji);
				int x = position.x;
				int y = position.y;
				this->mousePressed(x,y);
			}
			if (zdarzenie.type == sf::Event::MouseButtonPressed && zdarzenie.mouseButton.button == sf::Mouse::Right)
				this->currentMarked = nullptr;

		}
		sf::Vector2i position = sf::Mouse::getPosition(*this->oknoAplikacji);
		int x = position.x;
		int y = position.y;
		//if (x < 100 && y < 255)
		this->menu->menuTouch(x,y);
		this->oknoAplikacji->display();
	}
}

void AppManager::mousePressed(int x, int y)
{
	if (x < 100 && y < 255)
		this->menu->menuClicked(x,y);
	else if (this->currentMarked == nullptr)
	{
		this->currentMarked = this->findPawn(calculateX(x), calculateY(y));
		if(currentMarked != nullptr)
			this->mark->setPosition(currentMarked->getX()*111 + 185 - 111 - 4, currentMarked->getY() * 111 + 60 - 111 - 3);
	}
	else
	{
		if (this->gameMan->canMove(this->currentMarked->getX(), this->currentMarked->getY(), calculateX(x), calculateY(y)))
		{
			this->animation(calculateX(x), calculateY(y));
			this->currentMarked->setPosition(calculateX(x), calculateY(y));
			this->currentMarked = nullptr;
		}
	}
}

void AppManager::animation(int xnew, int ynew)
{
	int cx = this->currentMarked->getX();
	int cy = this->currentMarked->getY();

	int dx = ((cx * 111 + 185) - (xnew * 111 + 185) );
	int dy = ((cy * 111 + 60) - (ynew * 111 + 60) );
	cx--;
	cy--;
	cx = cx * 111 + 185;
	cy = cy * 111 + 60;

	for (int i = 0; i < abs(dx); i++)
	{
		if (dx < 0 && dy < 0)
			this->currentMarked->getSprite()->setPosition(cx + i, cy + i);
		else if (dx < 0 && dy > 0)
			this->currentMarked->getSprite()->setPosition(cx + i, cy - i);
		else if (dx > 0 && dy < 0)
			this->currentMarked->getSprite()->setPosition(cx - i, cy + i);
		else if (dx > 0 && dy > 0)
			this->currentMarked->getSprite()->setPosition(cx - i, cy - i);


		this->oknoAplikacji->draw(*board);
		this->oknoAplikacji->draw(*leftPanel);
		this->oknoAplikacji->draw(*rightPanel);
		this->menu->show();

		for (int i = 0; i < 24; i++)
			this->oknoAplikacji->draw(*this->pawns[i]->getSprite());

		this->oknoAplikacji->display();
	}
}

Pawn* AppManager::findPawn(int x, int y)
{
	for (int i = 0; i < 24; i++)
		if (pawns[i]->getX() == x && pawns[i]->getY() == y)
				return pawns[i];
	return nullptr;
}

int AppManager::calculateY(int a)
{
	a -= 60;
	return a / 111 + 1;
}

int AppManager::calculateX(int a)
{
	a -= 185;
	return a / 111 + 1;
}

sf::RenderWindow* AppManager::getWindow()
{
	return this->oknoAplikacji;
}

void AppManager::save()
{
	std::fstream file;
	file.open("save.txt");
	if(file.good() == false)
		this->oknoAplikacji->close();

	for (int i = 0; i < 24; i++)
	{
		file << this->pawns[i]->getX() << std::endl;
		file << this->pawns[i]->getY() << std::endl;
		file << this->pawns[i]->getColor() << std::endl;
	}
	file.close();
}

void AppManager::load()
{
	std::fstream file;
	file.open("save.txt");
	if (file.good() == false)
		this->oknoAplikacji->close();
	for (int i = 0; i < 24; i++)
	{
		int x, y, color;
		file >> x;
		file >> y;
		file >> color;
		this->pawns[i]->setPosition(x, y);
		this->pawns[i]->setColor(color);
	}
	file.close();
}

AppManager::~AppManager()
{
	delete this->oknoAplikacji;
	delete this->board;
	delete this->leftPanel;
	delete this->rightPanel;
	delete this->mark;
}
