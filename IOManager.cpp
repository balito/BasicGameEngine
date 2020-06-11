#include "IOManager.h"
#include <filesystem>
#include <fstream>
#include <string>
using namespace std;

bool IOManager::readFileToBuffer(string filePath, vector<unsigned char>& buffer)
{
	ifstream file(filePath, ios::binary);

	if (file.fail())
	{
		perror(filePath.c_str());
		return false;
	}
	//seek to the end;
	file.seekg(0, ios::end);

	//Get file size;
	int fileSize = file.tellg();
	file.seekg(0, ios::beg);

	//Reduce the file size from header bytes
	fileSize -= file.tellg();

	buffer.resize(fileSize);
	file.read((char *)&(buffer[0]), fileSize);
	file.close();

	return true; 
 
}