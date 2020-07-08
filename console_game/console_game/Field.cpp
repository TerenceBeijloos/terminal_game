#include "Field.h"

void Field::fill(const Pixel& c)
{
	for (unsigned int i = 0; i < m_Field.size(); i++)
	{
		m_Field[i].fill(c);
	}
}

void Field::fill(const Pixel& c, const Position& begin, const Position& end)
{
	for (unsigned int y = 0; y < (end.y - begin.y); y++)
	{
		for (unsigned int x = 0; x < (end.x - begin.x); x++)
		{
			m_Field[x][y] = c;
		}
	}
}

unsigned int Field::size() const
{
	return m_Field.size();
}

void Field::view()
{
}
