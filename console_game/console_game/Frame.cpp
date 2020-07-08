#include "Frame.h"
#include <iostream>

Frame::Frame(const int *frame, const Frame_size& size)
{
	m_Frame = frame;
	m_Size = size;
	m_Current_line = 0;
}

Frame::~Frame()
{
	//Do not delete m_Frame
}

std::string Frame::getline()
{
	if (m_Current_line == m_Size.height)
	{
		m_Current_line = 0;
		return "";
	}
	
	std::string line = "";

	for (unsigned int x = 0; x < m_Size.width; x++)
	{
		line += (char)m_Frame[(m_Current_line * m_Size.width) + x];
	}

	m_Current_line++;
	return line;
}

void Frame::print() const
{
	for (unsigned int y = 0; y < m_Size.height; y++)
	{
		for (unsigned int x = 0; x < m_Size.width; x++)
		{
			std::cout << (char)m_Frame[(y*m_Size.width)+x];
		}
		std::cout << std::endl;
	}

}

