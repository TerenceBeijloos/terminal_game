#include "Assembler.h"
#include "Frame.h"

//Assembler::Assembler()
//{
//	m_Field.fill(Pixel(' '));
//	m_Piority.fill((char)-128);
//}
//
//Assembler::~Assembler()
//{
//}

template<class Storage_type, class Frame_type>
Assembler<Storage_type, Frame_type>::Assembler()
{
		m_Field.fill(Pixel(' '));
		m_Piority.fill((char)-128);
}

template<class Storage_type, class Frame_type>
Assembler<Storage_type, Frame_type>::~Assembler()
{
}

void Assembler::add(Frame_type& frame, const Position& pos, const Pixel& priority)
{
	std::string line = frame.getline();
	unsigned int y = 0;

	while (line != "")
	{
		for (unsigned int x = 0; x < frame.get_size().width; x++)
		{
			if (m_Piority[x][y] < priority || m_Field[x][y] == Pixel(' '))
			{
				m_Piority[x][y] = priority;
				m_Field  [x][y]	= frame[x];
			}
		}
		y++;
		line = frame.getline();
	}
}

void Assembler::view_field()
{

}

void Assembler::view_priority()
{
}
