#include "ImageLoader.h"
#include "picoPNG.h"
#include "IOManager.h"
#include "Errors.h"

GLTexture ImageLoader::loadPNG(std::string filePath) {
	GLTexture texture = {}; //Initialize everything in struct to 0

	std::vector<unsigned char> in;
	std::vector<unsigned char> out;
	unsigned long width, height;

	//Fill vector in with binary data of filePath
	IOManager::readFileToBuffer(filePath, in);
	if (IOManager::readFileToBuffer(filePath, in) == false) {
		fatalError("Failed to load PNG file to buffer");
	}

	int errorCode = decodePNG(out, width, height, &(in[0]), in.size());
	if (errorCode != 0) {
		fatalError("decodePNG failed with error: " + std::to_string(errorCode));
	}

	//Create texture
	glGenTextures(1, &(texture.id));

	//Bind texture
	glBindTexture(GL_TEXTURE_2D, texture.id);
	//Upload image data to texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //has to do with mipmapping, uses linear interpolation
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0); //unbind current texture

	texture.width = width;
	texture.height = height;

	return texture;
}