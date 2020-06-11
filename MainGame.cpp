#include "MainGame.h"
#include <iostream>
#include <string>
#include "sprite.h"
#include "errors.h"
#include "ImageLoader.h"
using namespace std;

MainGame::MainGame() : _window(nullptr),
_screenWidth(1280),
_screenHeight(720),
_gameState(GameState::PLAY),
_time(0)
{
	 
}


void MainGame::run()
{	
	_playerTexture = ImageLoader::loadPNG("textures/bat.png");
	initSystems();
	_sprite.Init(-1.0f, -1.0f, 2.0f, 2.0f);
	gameLoop();


}

//The function initialize windows creation of SDL.
void MainGame::initSystems()
{

	SDL_Init(SDL_INIT_EVERYTHING);
	_window = SDL_CreateWindow("GameTest", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);

	if (_window == nullptr)
	{
		fatalError("Window cannot be created!!");
	 }

	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
	if (glContext == nullptr)
	{
		fatalError("Window cannot be created");

	}
	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		fatalError("Couldn't initialise GLEW");
	}

	glClearColor(1.0f, 0.0f, 0.4f, 1.0f);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	
	initShaders();
}

void MainGame::initShaders()
{
	_colorProgram.compileShaders("shaders/colorshading.vert", "shaders/colorshading.frag");
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexColor");
	_colorProgram.addAttribute("vertexUV");
	_colorProgram.linkShaders();


}
void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		processInput();
		_time += 0.1f;
		drawGame();		
	}

}
void MainGame::processInput() 
{
	SDL_Event evnt;

	while (SDL_PollEvent(&evnt ))
	{
		switch (evnt.type)
		{
		case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
		case SDL_MOUSEMOTION:
			cout << evnt.motion.x << "  " << evnt.motion.y << endl;
			break;

		}
	}


}
//Draws the game using OpenGL
void MainGame::drawGame()
{


	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_colorProgram.use();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _playerTexture.id);
	GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);
	//GLuint timeLocation = _colorProgram.getUniformLocation("time");
	//glUniform1f(timeLocation, _time);
	//Draw sprite
	_sprite.draw();
	glBindTexture(GL_TEXTURE_2D, 0);
	_colorProgram.unuse();
	


	//Swaps buffer for more info read documentation!
	SDL_GL_SwapWindow(_window);
}


