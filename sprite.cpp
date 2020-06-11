#include "sprite.h"
#include <glew.h>
#include "vertex.h"
#include <cstddef>
#include <string>

sprite::sprite() : _x(0), _y(0), _width(0), _height(0), _vboID(0)
{

}
sprite::~sprite()
{
	if (_vboID != 0)
	{
		glDeleteBuffers(1, &_vboID);
	}
}

void sprite::Init(float x, float y, float width, float height)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	//Next things specife screen coordinate space for the buffer
	if (_vboID == 0)
	{
		glGenBuffers(1, &_vboID);
	}
	vertex vertexData[6] = {};
	// First triangle of the buffer sry for hardcoding :D
	vertexData[0].setPosition(x + width, y + height);
	vertexData[0].setUV(1.0f, 1.0f);

	vertexData[1].setPosition(x, y + height);
	vertexData[1].setUV(0.0f, 1.0f);

	vertexData[2].setPosition(x, y);
	vertexData[2].setUV(0.0f, 0.0f);
	//Second triangle of the buffer same hardcoding :/
	vertexData[3].setPosition(x, y);
	vertexData[3].setUV(0.0f, 0.0f);

	vertexData[4].setPosition(x + width, y);
	vertexData[4].setUV(1.0f, 0.0f);

	vertexData[5].setPosition(x + width, y + height);
	vertexData[5].setUV(1.0f, 1.0f);

	for (int i = 0; i < 6; i++)
	{
		vertexData[i].setColor(255, 0, 255, 255);
	}

	vertexData[4].setColor(0, 0, 255, 255);
	vertexData[4].setColor(0, 255, 0, 255);
	//Bind buffer first then upload it
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void sprite::draw()
{

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);
	//glEnableVertexAttribArray(2);

	//Position attrib pointer
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, position));
	//Color attrib pointer
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(vertex), (void*)offsetof(vertex, color));
	//UV pointer
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, uv));


	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

}