#pragma once
#include <string>
#include <glew.h>
using namespace std;
class GLSLProgram
{
public:
	GLSLProgram();
	~GLSLProgram();
	void addAttribute(const string AttribName);
	void compileShaders(const string& vertexShaderFilePath, const string& fragmentShaderFilePath);
	void use();
	void unuse();
	void linkShaders();
	GLint getUniformLocation(const string& uniformName);
private:;
	void compileShader(const string& filePath, GLuint id);
	GLuint _programID;
	GLuint _shaderID;
	GLuint _fragmentID;
	int _numAttributes;
	   


};

