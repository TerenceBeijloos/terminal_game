#include "Texture_loader.h"
#include <string>
#include <iostream>

Texture_loader::Texture_loader()
{
}

Texture_loader::~Texture_loader()
{
}

Texture Texture_loader::load(const char* path)
{
	m_File.open(path);



	return Texture();
}

void Texture_loader::get_header(unsigned int& animation_count, Texture_size& size) const
{
	std::string line;
}
