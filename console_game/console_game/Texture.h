#pragma once
#include <map>

#define MAX_CHANGES 100

typedef struct {
	unsigned int width;
	unsigned int height;
} Texture_size;

typedef struct {
	unsigned int x;
	unsigned int y;
	char character;
} Change;

typedef struct {
	unsigned int count;
	Change* change;
} Animation_frame;

typedef struct {
	unsigned int count;
	unsigned int index;
	Animation_frame* frames;
} Animation;


class Texture
{
private:
	char** m_Texture;
	Texture_size m_Size;
	std::map<const char*, Animation> m_Animation;

public:

public:
	Texture();
	virtual ~Texture();

	void set_texture(const Texture_size& tex_size, const char** texture);
	char** get_texture(Texture_size& tex_size) const;

	void allocate_animation_space(const unsigned int new_size, const char* name, bool retain_memory = false);
	int add_to_animation(const Texture_size& tex_size, const char* name, const char** texture);
	char** get_animation(Texture_size& tex_size, const char* name, const unsigned int index);
	
	char** get_texture(Texture_size& tex_size) const;

	bool animation_available(const char* name);
private:
	void delete_texture();
	void delete_animation(const char* name);
};
