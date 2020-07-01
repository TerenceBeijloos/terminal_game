#pragma once

#include <fstream>
#include "Texture.h"

class Texture_loader
{
private:
	std::ifstream m_File;
public:

public:
	Texture_loader();
	virtual ~Texture_loader();

	Texture load(const char* path);

private:
	void get_header(unsigned int& animation_count, Texture_size& size) const;
	char* get_animation_name() const;
};

