#include "GameManager.h"
#include "AppManager.h"
#include <iostream>
#include <fstream>
#include <math.h>


GameManager::GameManager(AppManager* appman)
{
	this->application = appman;
	this->restart();
}

void GameManager::restart()
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			this->board[i][j] = NULL;

	std::ifstream plik;
	plik.open("plansza.txt");

	for (int i = 0; i < 24; i++)
	{
		if (i < 12)
		{
			int x, y;
			plik >> x >> y;
			this->board[y - 1][x - 1] = BLACK;
		}
		else
		{
			int x, y;
			plik >> x >> y;
			this->board[y - 1][x - 1] = WHITE;
		}
	}
	plik.close();
}

bool GameManager::canMove(int markedX, int markedY, int x, int y)
{
	if (board[y - 1][x - 1] == NULL)
	{
		if (abs(markedX - x) == 1 && abs(markedY - y) == 1)
		{
			board[y - 1][x - 1] = this->application->findPawn(markedX, markedY)->getColor();
			board[markedY - 1][markedX - 1] = NULL;
			return true;
		}
		else if (abs(markedX - x) == 2 && abs(markedY - y) == 2)
		{
			Pawn* p1 = this->application->findPawn(markedX + 1, markedY + 1);
			Pawn* p2 = this->application->findPawn(markedX - 1, markedY - 1);
			Pawn* p3 = this->application->findPawn(markedX + 1, markedY - 1);
			Pawn* p4 = this->application->findPawn(markedX - 1, markedY + 1);
			Pawn* mark = this->application->findPawn(markedX, markedY);
			if (p1 != nullptr && x == p1->getX() + 1 && y == p1->getY() + 1)
			{
				if (p1->getColor() != mark->getColor())
				{
					board[y - 1][x - 1] = mark->getColor();
					board[markedY - 1][markedX - 1] = NULL;
					board[p1->getY() - 1][p1->getX() - 1] = NULL;
					p1->setPosition(2000, 2000);
					return true;
				}
			}
			if (p2 != nullptr && x == p2->getX() - 1 && y == p2->getY() - 1)
			{
				if (p2->getColor() != mark->getColor())
				{
					board[y - 1][x - 1] = mark->getColor();
					board[markedY - 1][markedX - 1] = NULL;
					board[p2->getY() - 1][p2->getX() - 1] = NULL;
					p2->setPosition(2000, 2000);
					return true;
				}
			}
			if (p3 != nullptr && x == p3->getX() + 1 && y == p3->getY() - 1)
			{
				if (p3->getColor() != mark->getColor())
				{
					board[y - 1][x - 1] = mark->getColor();
					board[markedY - 1][markedX - 1] = NULL;
					board[p3->getY() - 1][p3->getX() - 1] = NULL;
					p3->setPosition(2000, 2000);
					return true;
				}
			}
			if (p4 != nullptr && x == p4->getX() - 1 && y == p4->getY() + 1)
			{
				if (p4->getColor() != mark->getColor())
				{
					board[y - 1][x - 1] = mark->getColor();
					board[markedY - 1][markedX - 1] = NULL;
					board[p4->getY() - 1][p4->getX() - 1] = NULL;
					p4->setPosition(2000, 2000);
					return true;
				}
			}
			return false;
		}
		else
			return false;
	}
	else
		return false;
}

GameManager::~GameManager()
{
}
