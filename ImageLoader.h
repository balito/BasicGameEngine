#pragma once
#include "GLtexture.h"
#include <string>
class ImageLoader
{
public:
	static GLTexture loadPNG(std::string filePath);


};

