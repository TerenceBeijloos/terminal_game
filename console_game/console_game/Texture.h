#pragma once
#include <map>

typedef struct {
	unsigned int width;
	unsigned int hight;
} Texture_size;

typedef struct {
	unsigned int count;
	char difference[][2];
} Animation_frame;

typedef std::map<const char*, Animation_frame> Animation;

class Texture
{
private:
	char* m_Texture;
	Texture_size m_Size;
	bool m_Animation;
	std::map<const char*, Animation> m_Animation;

public:

public:
	Texture();
	virtual ~Texture();

	void set_texture(const Texture_size& tex_size, const char** texture);
	void set_animation();
	bool animation_available();
private:

};
