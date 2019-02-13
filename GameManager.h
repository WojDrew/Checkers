#pragma once
#define BLACK 1
#define WHITE 2

class AppManager;

class GameManager
{
	AppManager* application;
	int board[8][8];
public:
	GameManager(AppManager* appman);
	void restart();
	bool canMove(int markedX, int markedY, int x, int y);
	~GameManager();
};

