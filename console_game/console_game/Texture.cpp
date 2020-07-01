#include "Texture.h"

Texture::Texture()
	: m_Texture(nullptr), m_Size({ 0,0 })
{
}

Texture::~Texture()
{
	this->delete_texture();

	for (auto const& animation : m_Animation) {
		this->delete_animation(animation.first);
	}
}

void Texture::set_texture(const Texture_size& tex_size, const char** texture)
{
	this->delete_texture();
	m_Texture = new char* [tex_size.width];

	for (unsigned x = 0; x < tex_size.width; x++)
	{
		m_Texture[x] = new char[tex_size.height];

		for (unsigned int y = 0; y < tex_size.height; y++)
		{
			m_Texture[x][y] = texture[x][y];
		}
	}

	m_Size = tex_size;
}

char** Texture::get_texture(Texture_size& tex_size) const
{
	tex_size = m_Size;
	return m_Texture;
}

void Texture::allocate_animation_space(const unsigned int new_size, const char* name, bool retain_memory)
{

	retain_memory = (m_Animation.find(name) != m_Animation.end()) ? retain_memory : false;

	Animation_frame* temp = nullptr;
	unsigned int retain_size = 0;
	if (retain_memory)
	{
		retain_size = m_Animation[name].count;
		temp = new Animation_frame[retain_size];

	}

	if (m_Animation.find(name) != m_Animation.end())
	{
		m_Animation.insert(std::pair<const char*, Animation>(name, Animation()));
	}
	else 
	{
		this->delete_animation(name);
	}

	m_Animation[name].frames = new Animation_frame[new_size];
	m_Animation[name].count = new_size;

	if (retain_memory)
	{
		memcpy(m_Animation[name].frames, temp, retain_size);
		m_Animation[name].index = retain_size;
	}
	else
	{
		m_Animation[name].index = 0;
	}

}

//TODO: currently animation cannot be larger than m_texture
int Texture::add_to_animation(const Texture_size& tex_size, const char* name, const char** texture)
{
	if (m_Size.height <= 0 || m_Size.width <= 0)
	{
		return -1; //Texture must exist before an animation is added
	}
	if (m_Animation.find(name) == m_Animation.end())
	{
		return -2; //Animation memory must be allocated first using allocate_animation_space
	}

	if (m_Animation[name].index >= m_Animation[name].count) {
		return -3; //More memory needs to be allocated using allocate_animation_space
	}

	unsigned int index = 0;
	Change changes[MAX_CHANGES];
	unsigned int count = 0;

	for (unsigned int x = 0; x < tex_size.width; x++)
	{
		for (unsigned int y = 0; y < tex_size.height && index < MAX_CHANGES; y++) {
			if (texture[x][y] != m_Texture[x][y])
			{
				changes[index++] = { x, y, texture[x][y] };
			}
		}
	}

	m_Animation[name].frames[m_Animation[name].index].change = new Change[index];
	memcpy(m_Animation[name].frames[m_Animation[name].index].change, changes, index);
	m_Animation[name].frames[m_Animation[name].index].count = index;
	m_Animation[name].index++;
}

char** Texture::get_animation(Texture_size& tex_size, const char* name, const unsigned int index) 
{
	char** temp = new char* [m_Size.width];
	for (unsigned x = 0; x < m_Size.width; x++)
	{
		temp[x] = new char[m_Size.height];
	}

	memcpy(&temp[0][0], &m_Texture[0][0], (m_Size.width*m_Size.height));

	for (unsigned int i = 0; i < m_Animation[name].frames[index].count; i++)
	{
		temp[m_Animation[name].frames[index].change[i].x][m_Animation[name].frames[index].change[i].y] = m_Animation[name].frames[index].change[i].character;
	}

	return temp;
}

bool Texture::animation_available(const char* name)
{
	return (m_Animation.find(name) != m_Animation.end());
}

void Texture::delete_texture()
{
	if (m_Texture != nullptr)
	{
		for (unsigned int x = 0; x < m_Size.width; x++)
		{
			delete[] m_Texture[x];
		}

		delete[] m_Texture;
	}
}

void Texture::delete_animation(const char* name)
{
	if (m_Animation.find(name) != m_Animation.end())
	{
		for (unsigned int i = 0; i < m_Animation[name].count; i++)
		{
			delete[] m_Animation[name].frames[i].change;
		}

		delete[] m_Animation[name].frames;
	}
}
