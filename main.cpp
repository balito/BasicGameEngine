#include <Windows.h>
#include <SDL.h>
#include <glew.h> 
#include <iostream>
#include "MainGame.h"
#include <string>
using namespace std;

int main(int argc, char** argv)
{
	MainGame mainGame;
	mainGame.run();

	return 0;
}