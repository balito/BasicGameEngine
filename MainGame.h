#pragma once
#include <SDL.h>
#include <glew.h>
#include "sprite.h"
#include "GLSLProgram.h"
#include "GLtexture.h"
using namespace std;

enum class GameState{PLAY, EXIT};
class MainGame
{
public: 
	MainGame();
	//~MainGame();

	void run();
private:
	void drawGame();
	void initShaders();
	void processInput();
	void gameLoop();
	void initSystems();
	SDL_Window* _window;
	int _screenWidth;
	int _screenHeight;
	GameState _gameState;
	sprite _sprite;
	GLSLProgram _colorProgram;
	GLTexture _playerTexture;
	float _time;

};