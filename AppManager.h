#pragma once
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Pawn.h"
#include "Menu.h"
#include "GameManager.h"
class AppManager
{
	sf::RenderWindow* oknoAplikacji;
	sf::Sprite* board;
	sf::Sprite* leftPanel;
	sf::Sprite* rightPanel;
	sf::Sprite* mark;
	Menu* menu;
	GameManager* gameMan;
	Pawn* pawns[24];
	Pawn* currentMarked;
public:
	AppManager();
	void display();
	void defaultBoard();
	void mousePressed(int x, int y);
	void animation(int xnew, int ynew);
	Pawn* findPawn(int x, int y);
	sf::RenderWindow* getWindow();
	void save();
	void load();
	int calculateX(int a);
	int calculateY(int a);
	~AppManager();
};

