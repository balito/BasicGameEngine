#include "errors.h"
#include <SDL.h>
#include <iostream>
#include <string>
#include <cstdlib>

void fatalError(string errorString)
{
	cout <<errorString << endl;
	cout << "Enter any key to quit" << endl;
	int tmp;
	cin >> tmp;
	SDL_Quit();
	exit(7);
}