#pragma once

#include <fstream>

class Texture_loader
{
private:
	std::ifstream m_File;
public:

public:
	Texture_loader();
	virtual ~Texture_loader();

	char* load(const char* path);
private:

};

