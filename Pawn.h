#pragma once
#include <SFML/Graphics.hpp>
#define BLACK 1
#define WHITE 2
class Pawn
{
	sf::Sprite* pawn;
	int x, y;
	int color;
public:
	Pawn(int color);
	void setPosition(int x, int y);
	sf::Sprite* getSprite();
	int getX();
	int getY();
	int getColor();
	void setColor(int color);
	~Pawn();
};

