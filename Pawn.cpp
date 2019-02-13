#include "Pawn.h"


Pawn::Pawn(int color)
{
	pawn = new sf::Sprite();
	this->color = color;
	if (color == BLACK)
	{
		sf::Texture* tekstura = new sf::Texture();
		tekstura->loadFromFile("Grafika/czarny.png");
		this->pawn->setTexture(*tekstura);
	}
	else
	{
		sf::Texture* tekstura = new sf::Texture();
		tekstura->loadFromFile("Grafika/bialy.png");
		this->pawn->setTexture(*tekstura);
	}
}

void Pawn::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
	x--;
	y--;
	this->pawn->setPosition(x*111 + 185,y*111 + 60);
}

sf::Sprite* Pawn::getSprite()
{
	return this->pawn;
}

int Pawn::getX()
{
	return this->x;
}
int Pawn::getY()
{
	return this->y;
}

int Pawn::getColor()
{
	return this->color;
}



void Pawn::setColor(int color)
{
	this->color = color;
}

Pawn::~Pawn()
{
	delete this->pawn;
}
