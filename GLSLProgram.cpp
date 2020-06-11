#include "GLSLProgram.h"
#include "errors.h"
#include <fstream>
#include <vector>
#include <string>
 

GLSLProgram::GLSLProgram() : _programID(0), _shaderID(0), _fragmentID(0), _numAttributes(0)
{

	}

GLSLProgram::~GLSLProgram()
{
	
}

void GLSLProgram::compileShaders(const string& vertexShaderFilePath, const string& fragmentShaderFilePath)
{

	 _programID = glCreateProgram();
	_shaderID = glCreateShader(GL_VERTEX_SHADER);
	if (_shaderID == 0)
	{
		fatalError("Vertex shader couldn't be created");
	}
	_fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
	if (_fragmentID == 0)
	{
		fatalError("Vertex shader couldn't be created");
	}
	compileShader(vertexShaderFilePath, _shaderID);	
	compileShader(fragmentShaderFilePath, _fragmentID);

	
}

void GLSLProgram::linkShaders() 
{

	// Attach our shaders to our program
	glAttachShader(_programID, _shaderID);
	glAttachShader(_programID, _fragmentID);

	// Link our program
	glLinkProgram(_programID);

	// Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(_programID, GL_LINK_STATUS, (int*)& isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<char> infoLog(maxLength);
		glGetProgramInfoLog(_programID, maxLength, &maxLength, &infoLog[0]);
		printf("%s\n", &(infoLog[0]));
		fatalError("Shader failed to link!");

		// We don't need the program anymore.
		glDeleteProgram(_programID);
		// Don't leak shaders either.
		glDeleteShader(_shaderID);
		glDeleteShader(_fragmentID);

		// Use the infoLog as you see fit.


		// In this simple program, we'll just leave
		return;
	}

	// Always detach shaders after a successful link.
	glDetachShader(_programID, _shaderID);
	glDetachShader(_programID, _fragmentID);
}
void GLSLProgram::addAttribute(const string AttribName)
{
	glBindAttribLocation(_programID, _numAttributes, AttribName.c_str());
	_numAttributes++;

}
GLint GLSLProgram::getUniformLocation(const string& uniformName)
{
	GLint location = glGetUniformLocation(_programID, uniformName.c_str());
	if (location == GL_INVALID_INDEX)
	{
		fatalError("Uniform" + uniformName + "not found in shader!");
	}
	return location;
}
void GLSLProgram::use()
{
	glUseProgram(_programID);
	for (GLint i = 0; i < _numAttributes; i++)
	{
		glEnableVertexAttribArray(i);
	}
}
void GLSLProgram::unuse() 
{
	glUseProgram(0);
	for (GLint i = 0; i < _numAttributes; i++)
	{
		glDisableVertexAttribArray(i);
	}
}

void GLSLProgram::compileShader(const string& filePath, GLuint id)
{

	ifstream vertexFile(filePath);
	if (vertexFile.fail())
	{
		perror(filePath.c_str());
		fatalError("Cannot open shader file" + filePath);
	}
	string fileContents = "";
	string line;

	while (getline(vertexFile, line))
	{
		fileContents += line + "\n";
	}
	vertexFile.close();
	const char* contentsPtr = fileContents.c_str();
	glShaderSource(id, 1, &contentsPtr, nullptr);
	glCompileShader(id);

	GLint logSize = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &logSize);
	if (logSize == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

		// Provide the infolog in whatever manor you deem best.
		// Exit with failure.
		glDeleteShader(id); // Don't leak the shader.
		fatalError("Shader" + filePath + " failed to compile ");
		printf("%s\n", &(errorLog[0]));

		return;
	}
}

