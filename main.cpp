#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "AppManager.h"
#include "Pawn.h"
#include <cstdlib>
#include <crtdbg.h>

int main(int argc, char **argv)
{
	AppManager appman;
	appman.display();
	//system("pause");
	return 0;
}