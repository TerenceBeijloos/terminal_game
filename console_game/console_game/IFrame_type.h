#pragma once
#include <string>

typedef struct {
	unsigned int width;
	unsigned int height;
} Frame_size;

class IFrame_type
{
private:
	Frame_size m_Size;

public:
	std::string getline();
	void print() const;

	inline Frame_size get_size() const { return m_Size; }
	virtual  const int& operator[](int i) const { return m_Frame[i]; }
private:

};

