#pragma once
#include <array>
#include "Map_types.h"

class Field
{
private:
	Field_type m_Field;
public:
	Field() = default;
	virtual ~Field() = default;

	void fill(const Pixel& c);
	void fill(const Pixel& c, const Position& begin, const Position& end);
	unsigned int size() const;

	inline const std::array<Pixel, FIELD_HEIGHT>& operator[](unsigned int x) const {return m_Field[x];}
	inline std::array<Pixel, FIELD_HEIGHT>& operator[](unsigned int x) {return m_Field[x];}

	void view();
private:

};

