#pragma once
#include <glew.h>
class sprite
{
public:
	sprite();
	~sprite();
	void draw();

	void Init(float x, float y, float width, float height);

private:
	float _x;
	float _y;
	float _width;
	float _height;
	GLuint _vboID;

};

