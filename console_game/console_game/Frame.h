#pragma once
#include <string>
#include "Map_types.h"


class Frame
{
private:
	const int* m_Frame;
	Frame_size m_Size;
	unsigned int m_Current_line;
public:
	Frame(const int *frame, const Frame_size& size);
	virtual ~Frame();

	std::string getline();
	void print() const;

	inline Frame_size get_size() const { return m_Size; }
	inline const int& operator[](int i) const { return m_Frame[i]; }

private:

};
